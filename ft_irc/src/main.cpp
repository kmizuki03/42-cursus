#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Server.hpp"

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

	if (argc != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	if (!parsePort(argv[1], port))
	{
		std::cerr << "Error: port must be a number between 1 and 65535"
			<< std::endl;
		return (1);
	}
	if (argv[2][0] == '\0')
	{
		std::cerr << "Error: password must not be empty" << std::endl;
		return (1);
	}
	signal(SIGINT, Server::handleSignal);
	signal(SIGQUIT, Server::handleSignal);
	signal(SIGTERM, Server::handleSignal);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		Server	server(port, argv[2]);

		server.run();
	}
	catch (const std::exception &exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
		return (1);
	}
	return (0);
}
