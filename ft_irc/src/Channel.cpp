#include "Channel.hpp"

#include "Client.hpp"
#include "Utils.hpp"

Channel::Channel(const std::string &name)
	: _name(name),
	_topicSet(false),
	_inviteOnly(false),
	_topicRestricted(false),
	_userLimit(0)
{
}

Channel::~Channel()
{
}

const std::string	&Channel::getName() const
{
	return (_name);
}

const std::string	&Channel::getTopic() const
{
	return (_topic);
}

bool	Channel::isTopicSet() const
{
	return (_topicSet);
}

void	Channel::setTopic(const std::string &topic)
{
	_topic = topic;
	_topicSet = !topic.empty();
}

void	Channel::addMember(Client *client)
{
	_members[client->getFd()] = client;
}

void	Channel::removeMember(int fd)
{
	_members.erase(fd);
	_operators.erase(fd);
	_invited.erase(fd);
}

bool	Channel::isMember(int fd) const
{
	return (_members.find(fd) != _members.end());
}

bool	Channel::isEmpty() const
{
	return (_members.empty());
}

const std::map<int, Client*>	&Channel::getMembers() const
{
	return (_members);
}

void	Channel::addOperator(int fd)
{
	_operators.insert(fd);
}

void	Channel::removeOperator(int fd)
{
	_operators.erase(fd);
}

bool	Channel::isOperator(int fd) const
{
	return (_operators.find(fd) != _operators.end());
}

void	Channel::addInvite(int fd)
{
	_invited.insert(fd);
}

void	Channel::removeInvite(int fd)
{
	_invited.erase(fd);
}

bool	Channel::isInvited(int fd) const
{
	return (_invited.find(fd) != _invited.end());
}

bool	Channel::isInviteOnly() const
{
	return (_inviteOnly);
}

void	Channel::setInviteOnly(bool on)
{
	_inviteOnly = on;
}

bool	Channel::isTopicRestricted() const
{
	return (_topicRestricted);
}

void	Channel::setTopicRestricted(bool on)
{
	_topicRestricted = on;
}

const std::string	&Channel::getKey() const
{
	return (_key);
}

void	Channel::setKey(const std::string &key)
{
	_key = key;
}

size_t	Channel::getUserLimit() const
{
	return (_userLimit);
}

void	Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}

bool	Channel::isFull() const
{
	return (_userLimit > 0 && _members.size() >= _userLimit);
}

std::string	Channel::getModeString() const
{
	std::string	modes("+");
	std::string	args;

	if (_inviteOnly)
		modes += "i";
	if (_topicRestricted)
		modes += "t";
	if (!_key.empty())
	{
		modes += "k";
		args += " " + _key;
	}
	if (_userLimit > 0)
	{
		modes += "l";
		args += " " + numberToString(static_cast<long>(_userLimit));
	}
	return (modes + args);
}

std::string	Channel::getNamesList() const
{
	std::string								names;
	std::map<int, Client*>::const_iterator	it;

	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (!names.empty())
			names += " ";
		if (isOperator(it->first))
			names += "@";
		names += it->second->getNickname();
	}
	return (names);
}
