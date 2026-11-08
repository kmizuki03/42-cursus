#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <cstddef>
# include <map>
# include <set>
# include <string>

class Client;

class Channel
{
public:
	explicit Channel(const std::string &name);
	~Channel();

	const std::string				&getName() const;

	const std::string				&getTopic() const;
	bool							isTopicSet() const;
	void							setTopic(const std::string &topic);

	void							addMember(Client *client);
	void							removeMember(int fd);
	bool							isMember(int fd) const;
	bool							isEmpty() const;
	const std::map<int, Client*>	&getMembers() const;

	void							addOperator(int fd);
	void							removeOperator(int fd);
	bool							isOperator(int fd) const;

	void							addInvite(int fd);
	void							removeInvite(int fd);
	bool							isInvited(int fd) const;

	bool							isInviteOnly() const;
	void							setInviteOnly(bool on);
	bool							isTopicRestricted() const;
	void							setTopicRestricted(bool on);
	const std::string				&getKey() const;
	void							setKey(const std::string &key);
	size_t							getUserLimit() const;
	void							setUserLimit(size_t limit);
	bool							isFull() const;

	std::string						getModeString() const;
	std::string						getNamesList() const;

private:
	Channel();
	Channel(const Channel &other);
	Channel	&operator=(const Channel &other);

	std::string				_name;
	std::string				_topic;
	bool					_topicSet;
	bool					_inviteOnly;
	bool					_topicRestricted;
	std::string				_key;
	size_t					_userLimit;
	std::map<int, Client*>	_members;
	std::set<int>			_operators;
	std::set<int>			_invited;
};

#endif
