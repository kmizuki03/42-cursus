#include "identify.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for (int i = 0; i < 5; i++)
	{
		Base	*ptr = generate();

		std::cout << "identify(ptr): ";
		identify(ptr);
		std::cout << "identify(ref): ";
		identify(*ptr);
		std::cout << "----------------" << std::endl;
		delete ptr;
	}

	return 0;
}
