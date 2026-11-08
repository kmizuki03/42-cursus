#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Error: could not open file." << std::endl;
			return 1;
		}

		BitcoinExchange	exchange;
		if (!exchange.loadDatabase("data.csv"))
		{
			return 1;
		}
		if (!exchange.processInput(argv[1]))
		{
			return 1;
		}

		return 0;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error: operation failed." << std::endl;
		return 1;
	}
}
