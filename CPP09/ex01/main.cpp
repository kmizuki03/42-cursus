#include "RPN.hpp"
#include <iostream>
#include <exception>

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}

		RPN	calculator;
		int	result = 0;

		if (!calculator.evaluate(argv[1], result))
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		std::cout << result << std::endl;

		return 0;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error: operation failed." << std::endl;
		return 1;
	}
}
