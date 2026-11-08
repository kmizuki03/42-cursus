#include "PmergeMe.hpp"
#include <iostream>
#include <exception>

int main(int argc, char **argv)
{
	try
	{
		PmergeMe	sorter;

		if (!sorter.execute(argc, argv))
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
