#ifndef BOT_HPP
# define BOT_HPP

# include <string>

# include "Message.hpp"

# define BOT_NICK "marvin"

class Bot
{
public:
	Bot(const std::string &host, int port, const std::string &password,
		const std::string &channel);
	~Bot();

	void		run();

	static void	handleSignal(int signum);

private:
	Bot();
	Bot(const Bot &other);
	Bot	&operator=(const Bot &other);

	static bool	_stopRequested;

	std::string	_host;
	int			_port;
	std::string	_password;
	std::string	_channel;
	std::string	_nickname;
	int			_fd;
	std::string	_recvBuffer;
	std::string	_sendBuffer;

	void		connectToServer();
	void		queueMessage(const std::string &message);
	void		processInputBuffer();
	void		processLine(const std::string &line);
	void		handlePrivmsg(const Message &msg);
	std::string	buildCommandReply(const std::string &text,
					const std::string &sender);
};

#endif
