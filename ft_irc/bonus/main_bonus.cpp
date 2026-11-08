#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Bot.hpp"
#include "Utils.hpp"

static bool	parsePort(const std::string &argument, int &port)
{
	if (argument.empty() || argument.size() > 5)
		return (false);
	for (size_t i = 0; i < argument.size(); ++i)
	{
		if (argument[i] < '0' || argument[i] > '9')
			return (false);
	}
	long	value = std::strtol(argument.c_str(), NULL, 10);
	if (value < 1 || value > 65535)
		return (false);
	port = static_cast<int>(value);
	return (true);
}

int	main(int argc, char **argv)
{
	int	port = 0;

	if (argc != 4 && argc != 5)
	{
		std::cerr << "Usage: ./ircbot <host> <port> <password> [channel]"
			<< std::endl;
		return (1);
	}
	if (!parsePort(argv[2], port))
	{
		std::cerr << "Error: port must be a number between 1 and 65535"
			<< std::endl;
		return (1);
	}
	std::string	channel = "#bot";

	if (argc == 5)
		channel = argv[4];
	if (!isValidChannelName(channel))
	{
		std::cerr << "Error: invalid channel name" << std::endl;
		return (1);
	}
	signal(SIGINT, Bot::handleSignal);
	signal(SIGQUIT, Bot::handleSignal);
	signal(SIGTERM, Bot::handleSignal);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		Bot	bot(argv[1], port, argv[3], channel);

		bot.run();
	}
	catch (const std::exception &exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
		return (1);
	}
	return (0);
}
