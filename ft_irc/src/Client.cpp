#include "Client.hpp"

Client::Client(int fd, const std::string &host)
	: _fd(fd),
	_host(host),
	_passOk(false),
	_registered(false),
	_markedForClose(false)
{
}

Client::~Client()
{
}

int	Client::getFd() const
{
	return (_fd);
}

const std::string	&Client::getHost() const
{
	return (_host);
}

const std::string	&Client::getNickname() const
{
	return (_nickname);
}

const std::string	&Client::getUsername() const
{
	return (_username);
}

const std::string	&Client::getRealname() const
{
	return (_realname);
}

std::string	Client::getPrefix() const
{
	std::string	nick = _nickname;
	std::string	user = _username;

	if (nick.empty())
		nick = "*";
	if (user.empty())
		user = "*";
	return (nick + "!" + user + "@" + _host);
}

void	Client::setNickname(const std::string &nickname)
{
	_nickname = nickname;
}

void	Client::setUsername(const std::string &username)
{
	_username = username;
}

void	Client::setRealname(const std::string &realname)
{
	_realname = realname;
}

bool	Client::isPassOk() const
{
	return (_passOk);
}

void	Client::setPassOk(bool ok)
{
	_passOk = ok;
}

bool	Client::hasNick() const
{
	return (!_nickname.empty());
}

bool	Client::hasUser() const
{
	return (!_username.empty());
}

bool	Client::isRegistered() const
{
	return (_registered);
}

void	Client::setRegistered(bool registered)
{
	_registered = registered;
}

bool	Client::isMarkedForClose() const
{
	return (_markedForClose);
}

void	Client::markForClose()
{
	_markedForClose = true;
}

std::string	&Client::recvBuffer()
{
	return (_recvBuffer);
}

std::string	&Client::sendBuffer()
{
	return (_sendBuffer);
}
