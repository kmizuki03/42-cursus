#include "Server.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"

void	Server::handleLine(Client *client, const std::string &line)
{
	Message	msg = parseMessage(line);

	if (msg.command.empty())
		return ;
	if (msg.command == "CAP")
		handleCap(client, msg);
	else if (msg.command == "PASS")
		handlePass(client, msg);
	else if (msg.command == "NICK")
		handleNick(client, msg);
	else if (msg.command == "USER")
		handleUser(client, msg);
	else if (msg.command == "PING")
		handlePing(client, msg);
	else if (msg.command == "PONG")
		;
	else if (msg.command == "QUIT")
		handleQuit(client, msg);
	else if (!client->isRegistered())
		sendNumeric(client, "451", ":You have not registered");
	else if (msg.command == "JOIN")
		handleJoin(client, msg);
	else if (msg.command == "PART")
		handlePart(client, msg);
	else if (msg.command == "PRIVMSG")
		handlePrivmsg(client, msg, false);
	else if (msg.command == "NOTICE")
		handlePrivmsg(client, msg, true);
	else if (msg.command == "KICK")
		handleKick(client, msg);
	else if (msg.command == "INVITE")
		handleInvite(client, msg);
	else if (msg.command == "TOPIC")
		handleTopic(client, msg);
	else if (msg.command == "MODE")
		handleMode(client, msg);
	else if (msg.command == "WHO")
		handleWho(client, msg);
	else
		sendNumeric(client, "421", msg.command + " :Unknown command");
}

void	Server::handleCap(Client *client, const Message &msg)
{
	if (msg.params.empty())
		return ;
	std::string	subCommand = toUpperString(msg.params[0]);

	if (subCommand == "LS")
		queueMessage(client, ":" SERVER_NAME " CAP * LS :");
	else if (subCommand == "REQ" && msg.params.size() > 1)
		queueMessage(client, ":" SERVER_NAME " CAP * NAK :" + msg.params[1]);
}

void	Server::handlePass(Client *client, const Message &msg)
{
	if (client->isRegistered())
	{
		sendNumeric(client, "462", ":You may not reregister");
		return ;
	}
	if (msg.params.empty())
	{
		sendNumeric(client, "461", "PASS :Not enough parameters");
		return ;
	}
	client->setPassOk(msg.params[0] == _password);
}

void	Server::handleNick(Client *client, const Message &msg)
{
	if (msg.params.empty() || msg.params[0].empty())
	{
		sendNumeric(client, "431", ":No nickname given");
		return ;
	}
	const std::string	&nickname = msg.params[0];

	if (!isValidNickname(nickname))
	{
		sendNumeric(client, "432", nickname + " :Erroneous nickname");
		return ;
	}
	Client	*existing = findClientByNick(nickname);
	if (existing && existing != client)
	{
		sendNumeric(client, "433", nickname + " :Nickname is already in use");
		return ;
	}
	if (client->isRegistered())
	{
		std::string	notification = ":" + client->getPrefix() + " NICK :"
			+ nickname;

		client->setNickname(nickname);
		broadcastToPeers(client, notification, true);
	}
	else
	{
		client->setNickname(nickname);
		tryCompleteRegistration(client);
	}
}

void	Server::handleUser(Client *client, const Message &msg)
{
	if (client->isRegistered())
	{
		sendNumeric(client, "462", ":You may not reregister");
		return ;
	}
	if (msg.params.size() < 4)
	{
		sendNumeric(client, "461", "USER :Not enough parameters");
		return ;
	}
	client->setUsername(msg.params[0]);
	client->setRealname(msg.params[3]);
	tryCompleteRegistration(client);
}

void	Server::tryCompleteRegistration(Client *client)
{
	if (client->isRegistered() || !client->hasNick() || !client->hasUser())
		return ;
	if (!client->isPassOk())
	{
		sendNumeric(client, "464", ":Password incorrect");
		queueMessage(client, "ERROR :Access denied, wrong password");
		disconnectClient(client, "Access denied");
		return ;
	}
	client->setRegistered(true);
	sendNumeric(client, "001", ":Welcome to the ft_irc network, "
		+ client->getPrefix());
	sendNumeric(client, "002", ":Your host is " SERVER_NAME
		", running version " SERVER_VERSION);
	sendNumeric(client, "003", ":This server was created " + _creationDate);
	sendNumeric(client, "004", SERVER_NAME " " SERVER_VERSION " o itkol");
}

void	Server::handlePing(Client *client, const Message &msg)
{
	if (msg.params.empty() || msg.params[0].empty())
	{
		sendNumeric(client, "409", ":No origin specified");
		return ;
	}
	queueMessage(client, ":" SERVER_NAME " PONG " SERVER_NAME " :"
		+ msg.params[0]);
}

void	Server::handleQuit(Client *client, const Message &msg)
{
	std::string	reason = "Quit";

	if (!msg.params.empty() && !msg.params[0].empty())
		reason += ": " + msg.params[0];
	queueMessage(client, "ERROR :Closing connection");
	disconnectClient(client, reason);
}

void	Server::handleWho(Client *client, const Message &msg)
{
	std::string	mask = "*";

	if (!msg.params.empty() && !msg.params[0].empty())
		mask = msg.params[0];
	Channel	*channel = findChannel(mask);

	if (channel)
	{
		std::map<int, Client*>::const_iterator	it;

		for (it = channel->getMembers().begin();
			it != channel->getMembers().end(); ++it)
		{
			std::string	flags = "H";

			if (channel->isOperator(it->first))
				flags += "@";
			sendNumeric(client, "352", channel->getName() + " "
				+ it->second->getUsername() + " " + it->second->getHost()
				+ " " SERVER_NAME " " + it->second->getNickname() + " "
				+ flags + " :0 " + it->second->getRealname());
		}
	}
	sendNumeric(client, "315", mask + " :End of /WHO list");
}
