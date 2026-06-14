/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:43 by kmizuki           #+#    #+#             */
/*   Updated: 2026/02/20 12:34:45 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	public:
		PhoneBook();

		bool add();
		void search() const;

	private:
		Contact _contacts[8];
		int _nextIndex;
		int _count;

		static std::string _promptNonEmpty(const std::string &label);
		static std::string _formatColumn(const std::string &value);
		static bool _parseIndex(const std::string &s, int &outIndex);
};

#endif
