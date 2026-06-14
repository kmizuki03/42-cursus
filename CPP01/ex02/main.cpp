/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:17:51 by kmizuki           #+#    #+#             */
/*   Updated: 2026/04/17 23:18:12 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main()
{
	std::string str = "HI THIS IS BRAIN";

	std::string* stringPTR = &str;

	std::string& stringREF = str;

	std::cout << std::string("=== Memory Addresses ===") << std::endl;
	std::cout << std::string("Address of str:        ") << &str << std::endl;
	std::cout << std::string("Address in stringPTR:  ") << stringPTR << std::endl;
	std::cout << std::string("Address of stringREF:  ") << &stringREF << std::endl;

	std::cout << std::string("\n=== Values ===") << std::endl;
	std::cout << std::string("Value of str:          ") << str << std::endl;
	std::cout << std::string("Value via stringPTR:   ") << *stringPTR << std::endl;
	std::cout << std::string("Value via stringREF:   ") << stringREF << std::endl;

	return (0);
}
