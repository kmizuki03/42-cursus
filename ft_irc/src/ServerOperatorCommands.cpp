#include "Server.hpp"

#include <cstdlib>

#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"

void	Server::handleKick(Client *client, const Message &msg)
{
	if (msg.params.size() < 2)
	{
		sendNumeric(client, "461", "KICK :Not enough parameters");
		return ;
	}
	Channel	*channel = findChannel(msg.params[0]);

	if (!channel)
	{
		sendNumeric(client, "403", msg.params[0] + " :No such channel");
		return ;
	}
	if (!channel->isMember(client->getFd()))
	{
		sendNumeric(client, "442", msg.params[0]
			+ " :You're not on that channel");
		return ;
	}
	if (!channel->isOperator(client->getFd()))
	{
		sendNumeric(client, "482", msg.params[0]
			+ " :You're not channel operator");
		return ;
	}
	std::vector<std::string>	targets = splitString(msg.params[1], ',');
	std::string					comment = client->getNickname();

	if (msg.params.size() > 2 && !msg.params[2].empty())
		comment = msg.params[2];
	if (targets.empty())
	{
		sendNumeric(client, "461", "KICK :Not enough parameters");
		return ;
	}
	for (size_t i = 0; i < targets.size(); ++i)
	{
		Client	*victim = findClientByNick(targets[i]);

		if (!victim || !channel->isMember(victim->getFd()))
		{
			sendNumeric(client, "441", targets[i] + " " + channel->getName()
				+ " :They aren't on that channel");
			continue ;
		}
		broadcastToChannel(channel, ":" + client->getPrefix() + " KICK "
			+ channel->getName() + " " + victim->getNickname() + " :"
			+ comment, -1);
		if (removeClientFromChannel(victim, channel))
			break ;
	}
}

void	Server::handleInvite(Client *client, const Message &msg)
{
	if (msg.params.size() < 2 || msg.params[0].empty()
		|| msg.params[1].empty())
	{
		sendNumeric(client, "461", "INVITE :Not enough parameters");
		return ;
	}
	Channel	*channel = findChannel(msg.params[1]);

	if (!channel)
	{
		sendNumeric(client, "403", msg.params[1] + " :No such channel");
		return ;
	}
	if (!channel->isMember(client->getFd()))
	{
		sendNumeric(client, "442", msg.params[1]
			+ " :You're not on that channel");
		return ;
	}
	if (channel->isInviteOnly() && !channel->isOperator(client->getFd()))
	{
		sendNumeric(client, "482", msg.params[1]
			+ " :You're not channel operator");
		return ;
	}
	Client	*target = findClientByNick(msg.params[0]);

	if (!target)
	{
		sendNumeric(client, "401", msg.params[0] + " :No such nick/channel");
		return ;
	}
	if (channel->isMember(target->getFd()))
	{
		sendNumeric(client, "443", target->getNickname() + " "
			+ channel->getName() + " :is already on channel");
		return ;
	}
	channel->addInvite(target->getFd());
	sendNumeric(client, "341", target->getNickname() + " "
		+ channel->getName());
	queueMessage(target, ":" + client->getPrefix() + " INVITE "
		+ target->getNickname() + " :" + channel->getName());
}

void	Server::handleTopic(Client *client, const Message &msg)
{
	if (msg.params.empty() || msg.params[0].empty())
	{
		sendNumeric(client, "461", "TOPIC :Not enough parameters");
		return ;
	}
	Channel	*channel = findChannel(msg.params[0]);

	if (!channel)
	{
		sendNumeric(client, "403", msg.params[0] + " :No such channel");
		return ;
	}
	if (!channel->isMember(client->getFd()))
	{
		sendNumeric(client, "442", msg.params[0]
			+ " :You're not on that channel");
		return ;
	}
	if (msg.params.size() == 1)
	{
		if (channel->isTopicSet())
			sendNumeric(client, "332", channel->getName() + " :"
				+ channel->getTopic());
		else
			sendNumeric(client, "331", channel->getName()
				+ " :No topic is set");
		return ;
	}
	if (channel->isTopicRestricted() && !channel->isOperator(client->getFd()))
	{
		sendNumeric(client, "482", msg.params[0]
			+ " :You're not channel operator");
		return ;
	}
	channel->setTopic(msg.params[1]);
	broadcastToChannel(channel, ":" + client->getPrefix() + " TOPIC "
		+ channel->getName() + " :" + msg.params[1], -1);
}

void	Server::handleMode(Client *client, const Message &msg)
{
	if (msg.params.empty() || msg.params[0].empty())
	{
		sendNumeric(client, "461", "MODE :Not enough parameters");
		return ;
	}
	if (isChannelPrefix(msg.params[0][0]))
		handleChannelMode(client, msg);
	else
		handleUserMode(client, msg);
}

void	Server::handleUserMode(Client *client, const Message &msg)
{
	Client	*target = findClientByNick(msg.params[0]);

	if (!target)
	{
		sendNumeric(client, "401", msg.params[0] + " :No such nick/channel");
		return ;
	}
	if (target != client)
	{
		sendNumeric(client, "502", ":Cannot change mode for other users");
		return ;
	}
	if (msg.params.size() == 1 || msg.params[1].empty())
		sendNumeric(client, "221", "+");
}

void	Server::handleChannelMode(Client *client, const Message &msg)
{
	Channel	*channel = findChannel(msg.params[0]);

	if (!channel)
	{
		sendNumeric(client, "403", msg.params[0] + " :No such channel");
		return ;
	}
	if (msg.params.size() == 1 || msg.params[1].empty())
	{
		sendNumeric(client, "324", channel->getName() + " "
			+ channel->getModeString());
		return ;
	}
	if (!channel->isMember(client->getFd()))
	{
		sendNumeric(client, "442", msg.params[0]
			+ " :You're not on that channel");
		return ;
	}
	if (!channel->isOperator(client->getFd()))
	{
		sendNumeric(client, "482", msg.params[0]
			+ " :You're not channel operator");
		return ;
	}
	const std::string	&modeString = msg.params[1];
	size_t				argIndex = 2;
	bool				adding = true;
	std::string			appliedModes;
	std::string			appliedArgs;
	char				appliedSign = 0;

	for (size_t i = 0; i < modeString.size(); ++i)
	{
		char		mode = modeString[i];
		bool		applied = false;
		std::string	arg;

		if (mode == '+' || mode == '-')
		{
			adding = (mode == '+');
			continue ;
		}
		if (mode == 'i')
		{
			channel->setInviteOnly(adding);
			applied = true;
		}
		else if (mode == 't')
		{
			channel->setTopicRestricted(adding);
			applied = true;
		}
		else if (mode == 'k')
		{
			if (adding)
			{
				if (argIndex >= msg.params.size()
					|| msg.params[argIndex].empty())
				{
					sendNumeric(client, "461",
						"MODE :Not enough parameters");
					continue ;
				}
				arg = msg.params[argIndex++];
				channel->setKey(arg);
			}
			else
			{
				if (argIndex < msg.params.size())
					++argIndex;
				channel->setKey("");
				arg = "*";
			}
			applied = true;
		}
		else if (mode == 'l')
		{
			if (adding)
			{
				if (argIndex >= msg.params.size()
					|| msg.params[argIndex].empty())
				{
					sendNumeric(client, "461",
						"MODE :Not enough parameters");
					continue ;
				}
				arg = msg.params[argIndex++];
				char	*end = NULL;
				long	limit = std::strtol(arg.c_str(), &end, 10);
				if (end == NULL || *end != '\0' || limit <= 0)
					continue ;
				channel->setUserLimit(static_cast<size_t>(limit));
			}
			else
				channel->setUserLimit(0);
			applied = true;
		}
		else if (mode == 'o')
		{
			if (argIndex >= msg.params.size()
				|| msg.params[argIndex].empty())
			{
				sendNumeric(client, "461", "MODE :Not enough parameters");
				continue ;
			}
			arg = msg.params[argIndex++];
			Client	*target = findClientByNick(arg);
			if (!target)
			{
				sendNumeric(client, "401", arg + " :No such nick/channel");
				continue ;
			}
			if (!channel->isMember(target->getFd()))
			{
				sendNumeric(client, "441", arg + " " + channel->getName()
					+ " :They aren't on that channel");
				continue ;
			}
			if (adding)
				channel->addOperator(target->getFd());
			else
				channel->removeOperator(target->getFd());
			arg = target->getNickname();
			applied = true;
		}
		else
		{
			sendNumeric(client, "472", std::string(1, mode)
				+ " :is unknown mode char to me");
		}
		if (applied)
		{
			char	sign = '-';

			if (adding)
				sign = '+';
			if (sign != appliedSign)
			{
				appliedModes += sign;
				appliedSign = sign;
			}
			appliedModes += mode;
			if (!arg.empty())
				appliedArgs += " " + arg;
		}
	}
	if (!appliedModes.empty())
		broadcastToChannel(channel, ":" + client->getPrefix() + " MODE "
			+ channel->getName() + " " + appliedModes + appliedArgs, -1);
}
