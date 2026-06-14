/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:16:26 by kmizuki           #+#    #+#             */
/*   Updated: 2026/04/21 16:58:31 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name)
{
}
Zombie::~Zombie()
{
	std::cout << _name << std::string(": Destroyed") << std::endl;
}

// 自己紹介メソッド
void Zombie::announce(void)
{
	std::cout << _name << std::string(": BraiiiiiiinnnzzzZ...") << std::endl;
}
