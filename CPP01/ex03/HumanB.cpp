/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:21:07 by kmizuki           #+#    #+#             */
/*   Updated: 2026/04/17 23:21:32 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{
}

void HumanB::setWeapon(Weapon& weapon)
{
	_weapon = &weapon;
}

// 攻撃メソッド
void HumanB::attack() const
{
	if (_weapon == NULL)
	{
		std::cout << _name << std::string(" has no weapon to attack with!") << std::endl;
		return;
	}
	std::cout << _name << std::string(" attacks with their ") << _weapon->getType() << std::endl;
}
