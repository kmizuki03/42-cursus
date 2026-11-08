#include "Server.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"

bool	Server::_stopRequested = false;

Server::Server(int port, const std::string &password)
	: _port(port),
	_password(password),
	_listenFd(-1)
{
	std::time_t	now = std::time(NULL);
	char		buffer[64];

	if (std::strftime(buffer, sizeof(buffer), "%a %b %d %Y",
			std::localtime(&now)) == 0)
		buffer[0] = '\0';
	_creationDate = buffer;
	setupSocket();
}

Server::~Server()
{
	closeAllConnections();
}

void	Server::handleSignal(int signum)
{
	(void)signum;
	_stopRequested = true;
}

void	Server::setupSocket()
{
	struct sockaddr_in	address;
	struct pollfd		listenPollFd;
	int					option = 1;

	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenFd < 0)
		throw std::runtime_error("socket() failed");
	if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &option,
			sizeof(option)) < 0)
	{
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("setsockopt() failed");
	}
	if (fcntl(_listenFd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("fcntl() failed");
	}
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(static_cast<unsigned short>(_port));
	if (bind(_listenFd, reinterpret_cast<struct sockaddr*>(&address),
			sizeof(address)) < 0)
	{
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("bind() failed (port already in use?)");
	}
	if (listen(_listenFd, SOMAXCONN) < 0)
	{
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("listen() failed");
	}
	listenPollFd.fd = _listenFd;
	listenPollFd.events = POLLIN;
	listenPollFd.revents = 0;
	_pollFds.push_back(listenPollFd);
}

void	Server::run()
{
	std::cout << "ircserv: listening on port " << _port << std::endl;
	for (; !_stopRequested; )
	{
		updatePollEvents();
		if (poll(&_pollFds[0], static_cast<nfds_t>(_pollFds.size()), -1) < 0)
			continue ;
		handleEvents();
		sweepClosedClients();
	}
	std::cout << "ircserv: shutting down" << std::endl;
}

void	Server::updatePollEvents()
{
	for (size_t i = 0; i < _pollFds.size(); ++i)
	{
		_pollFds[i].revents = 0;
		if (_pollFds[i].fd == _listenFd)
		{
			_pollFds[i].events = POLLIN;
			continue ;
		}
		std::map<int, Client*>::iterator it = _clients.find(_pollFds[i].fd);
		if (it == _clients.end())
			continue ;
		_pollFds[i].events = 0;
		if (!it->second->isMarkedForClose())
			_pollFds[i].events |= POLLIN;
		if (!it->second->sendBuffer().empty())
			_pollFds[i].events |= POLLOUT;
	}
}

void	Server::handleEvents()
{
	for (size_t i = 0; i < _pollFds.size(); ++i)
	{
		short	revents = _pollFds[i].revents;
		int		fd = _pollFds[i].fd;

		if (revents == 0)
			continue ;
		if (fd == _listenFd)
		{
			if (revents & POLLIN)
				acceptNewClient();
			continue ;
		}
		if (revents & (POLLERR | POLLHUP | POLLNVAL))
		{
			forceDisconnect(fd);
			continue ;
		}
		if (revents & POLLIN)
			receiveFromClient(fd);
		if (revents & POLLOUT)
			sendToClient(fd);
	}
}

void	Server::acceptNewClient()
{
	struct sockaddr_in	address;
	socklen_t			addressLen = sizeof(address);
	struct pollfd		clientPollFd;
	int					fd;

	fd = accept(_listenFd, reinterpret_cast<struct sockaddr*>(&address),
			&addressLen);
	if (fd < 0)
		return ;
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(fd);
		return ;
	}
	_clients[fd] = new Client(fd, inet_ntoa(address.sin_addr));
	clientPollFd.fd = fd;
	clientPollFd.events = POLLIN;
	clientPollFd.revents = 0;
	_pollFds.push_back(clientPollFd);
	std::cout << "ircserv: new connection from "
		<< inet_ntoa(address.sin_addr) << " (fd " << fd << ")" << std::endl;
}

void	Server::receiveFromClient(int fd)
{
	std::map<int, Client*>::iterator	it = _clients.find(fd);
	char								buffer[4096];
	ssize_t								bytesRead;

	if (it == _clients.end() || it->second->isMarkedForClose())
		return ;
	bytesRead = recv(fd, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0)
	{
		it->second->sendBuffer().clear();
		disconnectClient(it->second, "Connection closed");
		return ;
	}
	it->second->recvBuffer().append(buffer, bytesRead);
	processInputBuffer(it->second);
	if (it->second->recvBuffer().size() > 8192)
	{
		it->second->sendBuffer().clear();
		queueMessage(it->second, "ERROR :Input line too long");
		disconnectClient(it->second, "Flooding");
	}
}

void	Server::sendToClient(int fd)
{
	std::map<int, Client*>::iterator	it = _clients.find(fd);
	ssize_t								bytesSent;

	if (it == _clients.end() || it->second->sendBuffer().empty())
		return ;
	std::string	&outBuffer = it->second->sendBuffer();
	bytesSent = send(fd, outBuffer.c_str(), outBuffer.size(), 0);
	if (bytesSent > 0)
		outBuffer.erase(0, bytesSent);
}

void	Server::forceDisconnect(int fd)
{
	std::map<int, Client*>::iterator	it = _clients.find(fd);

	if (it == _clients.end())
		return ;
	it->second->sendBuffer().clear();
	disconnectClient(it->second, "Connection lost");
}

void	Server::sweepClosedClients()
{
	std::map<int, Client*>::iterator	it;

	for (it = _clients.begin(); it != _clients.end(); )
	{
		Client	*client = it->second;

		if (client->isMarkedForClose() && client->sendBuffer().empty())
		{
			int	fd = it->first;

			removePollFd(fd);
			close(fd);
			delete client;
			_clients.erase(it++);
			std::cout << "ircserv: closed connection (fd " << fd << ")"
				<< std::endl;
		}
		else
			++it;
	}
}

void	Server::removePollFd(int fd)
{
	for (size_t i = 0; i < _pollFds.size(); ++i)
	{
		if (_pollFds[i].fd == fd)
		{
			_pollFds.erase(_pollFds.begin() + i);
			return ;
		}
	}
}

void	Server::closeAllConnections()
{
	std::map<int, Client*>::iterator		clientIt;
	std::map<std::string, Channel*>::iterator	channelIt;

	for (clientIt = _clients.begin(); clientIt != _clients.end(); ++clientIt)
	{
		close(clientIt->first);
		delete clientIt->second;
	}
	_clients.clear();
	for (channelIt = _channels.begin(); channelIt != _channels.end();
		++channelIt)
		delete channelIt->second;
	_channels.clear();
	_pollFds.clear();
	if (_listenFd >= 0)
	{
		close(_listenFd);
		_listenFd = -1;
	}
}

void	Server::processInputBuffer(Client *client)
{
	std::string	&buffer = client->recvBuffer();
	size_t		pos;

	for (; !client->isMarkedForClose()
		&& (pos = buffer.find('\n')) != std::string::npos; )
	{
		std::string	line = buffer.substr(0, pos);

		buffer.erase(0, pos + 1);
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (!line.empty())
			handleLine(client, line);
	}
}

void	Server::queueMessage(Client *client, const std::string &message)
{
	client->sendBuffer() += message + "\r\n";
}

void	Server::sendNumeric(Client *client, const std::string &code,
	const std::string &text)
{
	std::string	nick = client->getNickname();

	if (nick.empty())
		nick = "*";
	queueMessage(client, ":" SERVER_NAME " " + code + " " + nick + " " + text);
}

Client	*Server::findClientByNick(const std::string &nickname) const
{
	std::map<int, Client*>::const_iterator	it;
	std::string								lowered = toLowerString(nickname);

	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (!it->second->isMarkedForClose()
			&& toLowerString(it->second->getNickname()) == lowered)
			return (it->second);
	}
	return (NULL);
}

Channel	*Server::findChannel(const std::string &name) const
{
	std::map<std::string, Channel*>::const_iterator	it;

	it = _channels.find(toLowerString(name));
	if (it == _channels.end())
		return (NULL);
	return (it->second);
}

Channel	*Server::getOrCreateChannel(const std::string &name, bool &created)
{
	Channel	*channel = findChannel(name);

	created = false;
	if (!channel)
	{
		channel = new Channel(name);
		_channels[toLowerString(name)] = channel;
		created = true;
	}
	return (channel);
}

void	Server::broadcastToChannel(Channel *channel,
	const std::string &message, int excludeFd)
{
	std::map<int, Client*>::const_iterator	it;

	for (it = channel->getMembers().begin();
		it != channel->getMembers().end(); ++it)
	{
		if (it->first != excludeFd)
			queueMessage(it->second, message);
	}
}

void	Server::broadcastToPeers(Client *client, const std::string &message,
	bool includeSelf)
{
	std::set<int>								targetFds;
	std::map<std::string, Channel*>::iterator	channelIt;
	std::map<int, Client*>::const_iterator		memberIt;
	std::set<int>::iterator						fdIt;

	if (includeSelf)
		targetFds.insert(client->getFd());
	for (channelIt = _channels.begin(); channelIt != _channels.end();
		++channelIt)
	{
		if (!channelIt->second->isMember(client->getFd()))
			continue ;
		for (memberIt = channelIt->second->getMembers().begin();
			memberIt != channelIt->second->getMembers().end(); ++memberIt)
			targetFds.insert(memberIt->first);
	}
	if (!includeSelf)
		targetFds.erase(client->getFd());
	for (fdIt = targetFds.begin(); fdIt != targetFds.end(); ++fdIt)
	{
		std::map<int, Client*>::iterator	it = _clients.find(*fdIt);

		if (it != _clients.end())
			queueMessage(it->second, message);
	}
}

bool	Server::removeClientFromChannel(Client *client, Channel *channel)
{
	channel->removeMember(client->getFd());
	if (channel->isEmpty())
	{
		_channels.erase(toLowerString(channel->getName()));
		delete channel;
		return (true);
	}
	return (false);
}

void	Server::partAllChannels(Client *client, const std::string &reason)
{
	std::vector<Channel*>						joined;
	std::map<std::string, Channel*>::iterator	it;

	for (it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second->isMember(client->getFd()))
			joined.push_back(it->second);
	}
	for (size_t i = 0; i < joined.size(); ++i)
	{
		broadcastToChannel(joined[i], ":" + client->getPrefix() + " PART "
			+ joined[i]->getName() + " :" + reason, -1);
		removeClientFromChannel(client, joined[i]);
	}
}

void	Server::disconnectClient(Client *client, const std::string &reason)
{
	std::vector<Channel*>						joined;
	std::map<std::string, Channel*>::iterator	it;

	if (client->isMarkedForClose())
		return ;
	if (client->isRegistered())
		broadcastToPeers(client, ":" + client->getPrefix() + " QUIT :"
			+ reason, false);
	for (it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second->isMember(client->getFd()))
			joined.push_back(it->second);
	}
	for (size_t i = 0; i < joined.size(); ++i)
		removeClientFromChannel(client, joined[i]);
	client->markForClose();
}

void	Server::sendNamesReply(Client *client, Channel *channel)
{
	sendNumeric(client, "353", "= " + channel->getName() + " :"
		+ channel->getNamesList());
	sendNumeric(client, "366", channel->getName() + " :End of /NAMES list");
}
