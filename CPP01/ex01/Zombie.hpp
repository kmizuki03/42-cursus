/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:16:56 by kmizuki           #+#    #+#             */
/*   Updated: 2026/04/17 23:16:57 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie
{
private:
	std::string _name;

public:
	Zombie();

	Zombie(std::string name);

	~Zombie();

	void setName(std::string name);

	void announce(void);
};

Zombie* zombieHorde(int N, std::string name);

#endif
