#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
public:
	Client(int fd, const std::string &host);
	~Client();

	int					getFd() const;
	const std::string	&getHost() const;
	const std::string	&getNickname() const;
	const std::string	&getUsername() const;
	const std::string	&getRealname() const;
	std::string			getPrefix() const;

	void				setNickname(const std::string &nickname);
	void				setUsername(const std::string &username);
	void				setRealname(const std::string &realname);

	bool				isPassOk() const;
	void				setPassOk(bool ok);
	bool				hasNick() const;
	bool				hasUser() const;
	bool				isRegistered() const;
	void				setRegistered(bool registered);
	bool				isMarkedForClose() const;
	void				markForClose();

	std::string			&recvBuffer();
	std::string			&sendBuffer();

private:
	Client();
	Client(const Client &other);
	Client	&operator=(const Client &other);

	int			_fd;
	std::string	_host;
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	bool		_passOk;
	bool		_registered;
	bool		_markedForClose;
	std::string	_recvBuffer;
	std::string	_sendBuffer;
};

#endif
