#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void	print(const T &elem)
{
	std::cout << elem << " ";
}

template <typename T>
void	increment(T &elem)
{
	elem += 1;
}

int main(void)
{
	int	intArray[5] = {1, 2, 3, 4, 5};

	std::cout << "int array: ";
	iter(intArray, 5, print<int>);
	std::cout << std::endl;

	iter(intArray, 5, increment<int>);
	std::cout << "after increment: ";
	iter(intArray, 5, print<int>);
	std::cout << std::endl;

	std::string	strArray[3] = {"hello", "template", "world"};
	std::cout << "string array: ";
	iter(strArray, 3, print<std::string>);
	std::cout << std::endl;

	const double	dblArray[4] = {1.1, 2.2, 3.3, 4.4};
	std::cout << "const double array: ";
	iter(dblArray, 4, print<double>);
	std::cout << std::endl;

	return 0;
}
