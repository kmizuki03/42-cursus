#include "Bot.hpp"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <poll.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#include "Utils.hpp"

bool	Bot::_stopRequested = false;

Bot::Bot(const std::string &host, int port, const std::string &password,
	const std::string &channel)
	: _host(host),
	_port(port),
	_password(password),
	_channel(channel),
	_nickname(BOT_NICK),
	_fd(-1)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	connectToServer();
}

Bot::~Bot()
{
	if (_fd >= 0)
		close(_fd);
}

void	Bot::handleSignal(int signum)
{
	(void)signum;
	_stopRequested = true;
}

void	Bot::connectToServer()
{
	struct addrinfo	hints;
	struct addrinfo	*result = NULL;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(_host.c_str(), numberToString(_port).c_str(), &hints,
			&result) != 0 || !result)
		throw std::runtime_error("getaddrinfo() failed");
	_fd = socket(result->ai_family, result->ai_socktype,
			result->ai_protocol);
	if (_fd < 0)
	{
		freeaddrinfo(result);
		throw std::runtime_error("socket() failed");
	}
	if (connect(_fd, result->ai_addr, result->ai_addrlen) < 0)
	{
		freeaddrinfo(result);
		close(_fd);
		_fd = -1;
		throw std::runtime_error("connect() failed (is ircserv running?)");
	}
	freeaddrinfo(result);
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(_fd);
		_fd = -1;
		throw std::runtime_error("fcntl() failed");
	}
	queueMessage("PASS " + _password);
	queueMessage("NICK " + _nickname);
	queueMessage("USER " + _nickname + " 0 * :" + _nickname + " the bot");
}

void	Bot::run()
{
	struct pollfd	pollFd;
	char			buffer[4096];
	ssize_t			bytes;

	std::cout << "ircbot: connected to " << _host << ":" << _port
		<< std::endl;
	for (; !_stopRequested; )
	{
		pollFd.fd = _fd;
		pollFd.events = POLLIN;
		if (!_sendBuffer.empty())
			pollFd.events |= POLLOUT;
		pollFd.revents = 0;
		if (poll(&pollFd, 1, -1) < 0)
			continue ;
		if (pollFd.revents & (POLLERR | POLLHUP | POLLNVAL))
			break ;
		if (pollFd.revents & POLLIN)
		{
			bytes = recv(_fd, buffer, sizeof(buffer), 0);
			if (bytes <= 0)
				break ;
			_recvBuffer.append(buffer, bytes);
			processInputBuffer();
		}
		if (pollFd.revents & POLLOUT)
		{
			bytes = send(_fd, _sendBuffer.c_str(), _sendBuffer.size(), 0);
			if (bytes > 0)
				_sendBuffer.erase(0, bytes);
		}
	}
	std::cout << "ircbot: disconnected" << std::endl;
}

void	Bot::queueMessage(const std::string &message)
{
	_sendBuffer += message + "\r\n";
}

void	Bot::processInputBuffer()
{
	size_t	pos;

	for (; (pos = _recvBuffer.find('\n')) != std::string::npos; )
	{
		std::string	line = _recvBuffer.substr(0, pos);

		_recvBuffer.erase(0, pos + 1);
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (!line.empty())
			processLine(line);
	}
}

void	Bot::processLine(const std::string &line)
{
	Message	msg = parseMessage(line);

	if (msg.command == "PING")
	{
		std::string	pongArg;

		if (!msg.params.empty())
			pongArg = msg.params[0];
		queueMessage("PONG :" + pongArg);
	}
	else if (msg.command == "001")
		queueMessage("JOIN " + _channel);
	else if (msg.command == "433")
	{
		_nickname += "_";
		queueMessage("NICK " + _nickname);
	}
	else if (msg.command == "464")
		_stopRequested = true;
	else if (msg.command == "INVITE" && msg.params.size() > 1)
		queueMessage("JOIN " + msg.params[1]);
	else if (msg.command == "PRIVMSG" && msg.params.size() > 1)
		handlePrivmsg(msg);
}

void	Bot::handlePrivmsg(const Message &msg)
{
	std::string	sender = msg.prefix.substr(0, msg.prefix.find('!'));
	std::string	target = msg.params[0];
	std::string	text = msg.params[1];
	bool		isChannelMessage = !target.empty()
		&& isChannelPrefix(target[0]);

	if (sender.empty())
		return ;
	if (isChannelMessage && (text.empty() || text[0] != '!'))
		return ;
	std::string	reply = buildCommandReply(text, sender);

	if (reply.empty())
		return ;
	if (isChannelMessage)
		queueMessage("PRIVMSG " + target + " :" + reply);
	else
		queueMessage("PRIVMSG " + sender + " :" + reply);
}

std::string	Bot::buildCommandReply(const std::string &text,
	const std::string &sender)
{
	if (text.empty())
		return ("Hi " + sender + "! Try !help to see what I can do.");
	std::string	command = toLowerString(text.substr(0, text.find(' ')));

	if (command == "!help")
		return ("Available commands: !help !time !dice !8ball !about");
	if (command == "!time")
	{
		std::time_t	now = std::time(NULL);
		char		buffer[64];

		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",
			std::localtime(&now));
		return (sender + ": it is " + std::string(buffer));
	}
	if (command == "!dice")
		return (sender + " rolled a "
			+ numberToString(std::rand() % 6 + 1));
	if (command == "!8ball")
	{
		static const char	*answers[] = {
			"It is certain.", "Ask again later.", "Don't count on it.",
			"Outlook good.", "Very doubtful.", "Without a doubt."
		};

		return (sender + ": " + answers[std::rand() % 6]);
	}
	if (command == "!about")
		return ("I am " + _nickname
			+ ", a bot for the ft_irc project. Here I am, "
			"brain the size of a planet, and they ask me to roll dice.");
	if (text[0] == '!')
		return (sender + ": unknown command, try !help");
	return ("Hi " + sender + "! Try !help to see what I can do.");
}
