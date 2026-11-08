#ifndef SERVER_HPP
# define SERVER_HPP

# include <map>
# include <string>
# include <vector>
# include <poll.h>

# include "Message.hpp"

# define SERVER_NAME "ircserv"
# define SERVER_VERSION "1.0"

class Client;
class Channel;

class Server
{
public:
	Server(int port, const std::string &password);
	~Server();

	void		run();

	static void	handleSignal(int signum);

private:
	Server();
	Server(const Server &other);
	Server	&operator=(const Server &other);

	static bool						_stopRequested;

	int								_port;
	std::string						_password;
	int								_listenFd;
	std::string						_creationDate;
	std::vector<struct pollfd>		_pollFds;
	std::map<int, Client*>			_clients;
	std::map<std::string, Channel*>	_channels;

	// event loop
	void	setupSocket();
	void	updatePollEvents();
	void	handleEvents();
	void	acceptNewClient();
	void	receiveFromClient(int fd);
	void	sendToClient(int fd);
	void	forceDisconnect(int fd);
	void	sweepClosedClients();
	void	removePollFd(int fd);
	void	closeAllConnections();

	// input processing
	void	processInputBuffer(Client *client);
	void	handleLine(Client *client, const std::string &line);

	// command handlers
	void	handleCap(Client *client, const Message &msg);
	void	handlePass(Client *client, const Message &msg);
	void	handleNick(Client *client, const Message &msg);
	void	handleUser(Client *client, const Message &msg);
	void	handlePing(Client *client, const Message &msg);
	void	handleQuit(Client *client, const Message &msg);
	void	handleWho(Client *client, const Message &msg);
	void	handleJoin(Client *client, const Message &msg);
	void	handlePart(Client *client, const Message &msg);
	void	handlePrivmsg(Client *client, const Message &msg, bool isNotice);
	void	handleKick(Client *client, const Message &msg);
	void	handleInvite(Client *client, const Message &msg);
	void	handleTopic(Client *client, const Message &msg);
	void	handleMode(Client *client, const Message &msg);
	void	handleUserMode(Client *client, const Message &msg);
	void	handleChannelMode(Client *client, const Message &msg);

	// helpers
	void	queueMessage(Client *client, const std::string &message);
	void	sendNumeric(Client *client, const std::string &code,
				const std::string &text);
	void	tryCompleteRegistration(Client *client);
	Client	*findClientByNick(const std::string &nickname) const;
	Channel	*findChannel(const std::string &name) const;
	Channel	*getOrCreateChannel(const std::string &name, bool &created);
	void	broadcastToChannel(Channel *channel, const std::string &message,
				int excludeFd);
	void	broadcastToPeers(Client *client, const std::string &message,
				bool includeSelf);
	bool	removeClientFromChannel(Client *client, Channel *channel);
	void	partAllChannels(Client *client, const std::string &reason);
	void	disconnectClient(Client *client, const std::string &reason);
	void	sendNamesReply(Client *client, Channel *channel);
};

#endif
