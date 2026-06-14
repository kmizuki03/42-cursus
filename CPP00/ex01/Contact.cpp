/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:33:32 by kmizuki           #+#    #+#             */
/*   Updated: 2026/02/20 12:33:37 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
	: _firstName(), _lastName(), _nickname(), _phoneNumber(),_darkestSecret()
{
}

void Contact::setFirstName(const std::string &value)
{
	_firstName = value;
}

void Contact::setLastName(const std::string &value)
{
	_lastName = value;
}

void Contact::setNickname(const std::string &value)
{
	_nickname = value;
}

void Contact::setPhoneNumber(const std::string &value)
{
	_phoneNumber = value;
}

void Contact::setDarkestSecret(const std::string &value)
{
	_darkestSecret = value;
}

const std::string &Contact::getFirstName() const
{
	return (_firstName);
}

const std::string &Contact::getLastName() const
{
	return (_lastName);
}

const std::string &Contact::getNickname() const
{
	return (_nickname);
}

const std::string &Contact::getPhoneNumber() const
{
	return (_phoneNumber);
}

const std::string &Contact::getDarkestSecret() const
{
	return (_darkestSecret);
}

bool Contact::isEmpty() const
{
	return (_firstName.empty() && _lastName.empty() && _nickname.empty() && _phoneNumber.empty() && _darkestSecret.empty());
}
