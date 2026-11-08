#include "Server.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"

void	Server::handleJoin(Client *client, const Message &msg)
{
	if (msg.params.empty())
	{
		sendNumeric(client, "461", "JOIN :Not enough parameters");
		return ;
	}
	if (msg.params[0] == "0")
	{
		partAllChannels(client, client->getNickname());
		return ;
	}
	std::vector<std::string>	names = splitString(msg.params[0], ',');
	std::vector<std::string>	keys;

	if (names.empty())
	{
		sendNumeric(client, "461", "JOIN :Not enough parameters");
		return ;
	}
	if (msg.params.size() > 1)
		keys = splitString(msg.params[1], ',');
	for (size_t i = 0; i < names.size(); ++i)
	{
		std::string	key;

		if (i < keys.size())
			key = keys[i];
		if (!isValidChannelName(names[i]))
		{
			sendNumeric(client, "403", names[i] + " :No such channel");
			continue ;
		}
		bool	created = false;
		Channel	*channel = getOrCreateChannel(names[i], created);

		if (channel->isMember(client->getFd()))
			continue ;
		if (channel->isInviteOnly() && !channel->isInvited(client->getFd()))
		{
			sendNumeric(client, "473", channel->getName()
				+ " :Cannot join channel (+i)");
			continue ;
		}
		if (!channel->getKey().empty() && key != channel->getKey())
		{
			sendNumeric(client, "475", channel->getName()
				+ " :Cannot join channel (+k)");
			continue ;
		}
		if (channel->isFull())
		{
			sendNumeric(client, "471", channel->getName()
				+ " :Cannot join channel (+l)");
			continue ;
		}
		channel->removeInvite(client->getFd());
		channel->addMember(client);
		if (created)
			channel->addOperator(client->getFd());
		broadcastToChannel(channel, ":" + client->getPrefix() + " JOIN :"
			+ channel->getName(), -1);
		if (channel->isTopicSet())
			sendNumeric(client, "332", channel->getName() + " :"
				+ channel->getTopic());
		sendNamesReply(client, channel);
	}
}

void	Server::handlePart(Client *client, const Message &msg)
{
	if (msg.params.empty())
	{
		sendNumeric(client, "461", "PART :Not enough parameters");
		return ;
	}
	std::vector<std::string>	names = splitString(msg.params[0], ',');
	std::string					reason = client->getNickname();

	if (msg.params.size() > 1 && !msg.params[1].empty())
		reason = msg.params[1];
	if (names.empty())
	{
		sendNumeric(client, "461", "PART :Not enough parameters");
		return ;
	}
	for (size_t i = 0; i < names.size(); ++i)
	{
		Channel	*channel = findChannel(names[i]);

		if (!channel)
		{
			sendNumeric(client, "403", names[i] + " :No such channel");
			continue ;
		}
		if (!channel->isMember(client->getFd()))
		{
			sendNumeric(client, "442", names[i]
				+ " :You're not on that channel");
			continue ;
		}
		broadcastToChannel(channel, ":" + client->getPrefix() + " PART "
			+ channel->getName() + " :" + reason, -1);
		removeClientFromChannel(client, channel);
	}
}

void	Server::handlePrivmsg(Client *client, const Message &msg,
	bool isNotice)
{
	std::string	commandName = "PRIVMSG";

	if (isNotice)
		commandName = "NOTICE";
	if (msg.params.empty())
	{
		if (!isNotice)
			sendNumeric(client, "411", ":No recipient given (PRIVMSG)");
		return ;
	}
	if (msg.params.size() < 2 || msg.params[1].empty())
	{
		if (!isNotice)
			sendNumeric(client, "412", ":No text to send");
		return ;
	}
	std::vector<std::string>	targets = splitString(msg.params[0], ',');
	const std::string			&text = msg.params[1];

	if (targets.empty())
	{
		if (!isNotice)
			sendNumeric(client, "411", ":No recipient given (PRIVMSG)");
		return ;
	}
	for (size_t i = 0; i < targets.size(); ++i)
	{
		if (isChannelPrefix(targets[i][0]))
		{
			Channel	*channel = findChannel(targets[i]);

			if (!channel)
			{
				if (!isNotice)
					sendNumeric(client, "403", targets[i]
						+ " :No such channel");
				continue ;
			}
			if (!channel->isMember(client->getFd()))
			{
				if (!isNotice)
					sendNumeric(client, "404", targets[i]
						+ " :Cannot send to channel");
				continue ;
			}
			broadcastToChannel(channel, ":" + client->getPrefix() + " "
				+ commandName + " " + channel->getName() + " :" + text,
				client->getFd());
		}
		else
		{
			Client	*target = findClientByNick(targets[i]);

			if (!target)
			{
				if (!isNotice)
					sendNumeric(client, "401", targets[i]
						+ " :No such nick/channel");
				continue ;
			}
			queueMessage(target, ":" + client->getPrefix() + " "
				+ commandName + " " + target->getNickname() + " :" + text);
		}
	}
}
