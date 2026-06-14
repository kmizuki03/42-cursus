/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:35 by kmizuki           #+#    #+#             */
/*   Updated: 2026/02/20 12:34:37 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>

PhoneBook::PhoneBook() : _contacts(), _nextIndex(0), _count(0)
{
}

std::string PhoneBook::_promptNonEmpty(const std::string &label)
{
	while (true)
	{
		std::cout << label;
		std::string input;
		if (!std::getline(std::cin, input))
			return (std::string());
		if (!input.empty())
			return (input);
		std::cout << "Empty input is not allowed." << std::endl;
	}
}

std::string PhoneBook::_formatColumn(const std::string &value)
{
	if (value.length() <= 10)
		return (value);
	return (value.substr(0, 9) + ".");
}

bool PhoneBook::_parseIndex(const std::string &s, int &outIndex)
{
	int	result;

	if (s.empty())
		return (false);
	result = 0;
	for (std::string::size_type i = 0; i < s.size(); ++i)
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		result = (result * 10) + (s[i] - '0');
		if (result > 8)
			break ;
	}
	outIndex = result;
	return (true);
}

bool PhoneBook::add()
{
	std::string firstName = _promptNonEmpty("First name: ");
	if (!std::cin)
		return (false);
	std::string lastName = _promptNonEmpty("Last name: ");
	if (!std::cin)
		return (false);
	std::string nickname = _promptNonEmpty("Nickname: ");
	if (!std::cin)
		return (false);
	std::string phoneNumber = _promptNonEmpty("Phone number: ");
	if (!std::cin)
		return (false);
	std::string darkestSecret = _promptNonEmpty("Darkest secret: ");
	if (!std::cin)
		return (false);
	Contact &c = _contacts[_nextIndex];
	c.setFirstName(firstName);
	c.setLastName(lastName);
	c.setNickname(nickname);
	c.setPhoneNumber(phoneNumber);
	c.setDarkestSecret(darkestSecret);
	_nextIndex = (_nextIndex + 1) % 8;
	if (_count < 8)
		++_count;
	std::cout << "Contact saved." << std::endl;
	return (true);
}

void PhoneBook::search() const
{
	if (_count == 0)
	{
		std::cout << "PhoneBook is empty." << std::endl;
		return ;
	}

	std::cout << std::setw(10) << "index" << "|" << std::setw(10) << "first name"
				<< "|" << std::setw(10) << "last name" << "|" << std::setw(10) << "nickname" << std::endl;
	for (int i = 0; i < _count; ++i)
	{
		const Contact &c = _contacts[i];
		std::cout << std::setw(10) << (i
			+ 1) << "|" << std::setw(10) << _formatColumn(c.getFirstName()) << "|" << std::setw(10) << _formatColumn(c.getLastName()) << "|" << std::setw(10) << _formatColumn(c.getNickname()) << std::endl;
	}

	std::cout << "Index to display: ";
	std::string input;
	if (!std::getline(std::cin, input))
		return ;
	int index = 0;
	if (!_parseIndex(input, index) || index < 1 || index > _count)
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}

	const Contact &c = _contacts[index - 1];
	std::cout << "First name: " << c.getFirstName() << std::endl;
	std::cout << "Last name: " << c.getLastName() << std::endl;
	std::cout << "Nickname: " << c.getNickname() << std::endl;
	std::cout << "Phone number: " << c.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << c.getDarkestSecret() << std::endl;
}
