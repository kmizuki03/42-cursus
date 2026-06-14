/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:34:02 by kmizuki           #+#    #+#             */
/*   Updated: 2026/04/21 17:29:30 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void Harl::debug(void)
{
	std::cout << std::string("[ DEBUG ]") << std::endl;
	std::cout << std::string("I love having extra bacon for my ") << std::string("7XL-double-cheese-triple-pickle-special-ketchup burger. ") << std::string("I really do!") << std::endl;
}

void Harl::info(void)
{
	std::cout << std::string("[ INFO ]") << std::endl;
	std::cout << std::string("I cannot believe adding extra bacon costs more money. ") << std::string("You didn't put enough bacon in my burger! ") << std::string("If you did, I wouldn't be asking for more!") << std::endl;
}

void Harl::warning(void)
{
	std::cout << std::string("[ WARNING ]") << std::endl;
	std::cout << std::string("I think I deserve to have some extra bacon for free. ") << std::string("I've been coming for years whereas you started working here ") << std::string("since last month.") << std::endl;
}

void Harl::error(void)
{
	std::cout << std::string("[ ERROR ]") << std::endl;
	std::cout << std::string("This is unacceptable! I want to speak to the manager now.") << std::endl;
}

void Harl::complain(std::string level)
{
	int i = 0;
	void (Harl::*functions[])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	std::string levels[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};

	while(i < 4)
	{
		if (level == levels[i])
		{
			(this->*functions[i])();
			return;
		}
		i++;
	}

	std::cout << std::string("[ UNKNOWN ]") << std::endl;
	std::cout << std::string("Invalid complaint level: ") << level << std::endl;
}
