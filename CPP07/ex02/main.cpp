#include "Array.hpp"
#include <iostream>
#include <string>

int main(void)
{
	Array<int>	empty;
	std::cout << "empty size: " << empty.size() << std::endl;

	Array<int>	numbers(5);
	std::cout << "numbers size: " << numbers.size() << std::endl;
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		numbers[i] = static_cast<int>(i) * 10;
	}
	std::cout << "numbers: ";
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "--- deep copy test ---" << std::endl;
	Array<int>	copy(numbers);
	copy[0] = 999;
	std::cout << "original[0]: " << numbers[0] << std::endl;
	std::cout << "copy[0]:     " << copy[0] << std::endl;

	std::cout << "--- assignment test ---" << std::endl;
	Array<int>	assigned;
	assigned = numbers;
	assigned[1] = 777;
	std::cout << "original[1]: " << numbers[1] << std::endl;
	std::cout << "assigned[1]: " << assigned[1] << std::endl;

	std::cout << "--- out of bounds test ---" << std::endl;
	try
	{
		std::cout << numbers[42] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	Array<std::string>	words(2);
	words[0] = "hello";
	words[1] = "array";
	std::cout << "words: " << words[0] << " " << words[1] << std::endl;

	return 0;
}
