/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 13:48:36 by kmizuki           #+#    #+#             */
/*   Updated: 2026/05/30 13:48:37 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main(void)
{
	std::cout << "=== Creating ScavTrap ===" << std::endl;
	ScavTrap scav1("ST-001");

	std::cout << "\n=== ScavTrap actions ===" << std::endl;
	scav1.attack("Enemy");
	scav1.takeDamage(30);
	scav1.beRepaired(20);
	scav1.guardGate();

	std::cout << "\n=== Comparing with ClapTrap ===" << std::endl;
	ClapTrap clap1("CT-001");
	clap1.attack("Target");
	scav1.attack("Target");

	std::cout << "\n=== Testing copy ===" << std::endl;
	ScavTrap scav2(scav1);
	ScavTrap scav3("ST-003");
	scav3 = scav1;

	std::cout << "\n=== Destructors ===" << std::endl;
	return (0);
}
