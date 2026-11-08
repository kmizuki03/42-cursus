#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(void)
{
	Span	sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << "--- full span exception ---" << std::endl;
	try
	{
		sp.addNumber(42);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "--- no span exception ---" << std::endl;
	try
	{
		Span	tiny(1);
		tiny.addNumber(1);
		tiny.shortestSpan();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "--- 10000 numbers with iterator range ---" << std::endl;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	std::vector<int>	bulk;
	for (int i = 0; i < 10000; i++)
	{
		bulk.push_back(std::rand());
	}

	Span	big(10000);
	big.addRange(bulk.begin(), bulk.end());
	std::cout << "shortestSpan: " << big.shortestSpan() << std::endl;
	std::cout << "longestSpan:  " << big.longestSpan() << std::endl;

	return 0;
}
