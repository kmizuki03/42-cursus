/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 13:49:13 by kmizuki           #+#    #+#             */
/*   Updated: 2026/05/30 13:49:14 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	std::cout << "=== Creating different robot types ===" << std::endl;
	ClapTrap clap("CT-001");
	ScavTrap scav("ST-001");
	FragTrap frag("FT-001");

	std::cout << "\n=== Testing FragTrap ===" << std::endl;
	frag.attack("Enemy");
	frag.takeDamage(40);
	frag.beRepaired(20);
	frag.highFivesGuys();

	std::cout << "\n=== Comparing attacks ===" << std::endl;
	clap.attack("Target");
	scav.attack("Target");
	frag.attack("Target");

	std::cout << "\n=== Special abilities ===" << std::endl;
	scav.guardGate();
	frag.highFivesGuys();

	std::cout << "\n=== Testing copy ===" << std::endl;
	FragTrap frag2(frag);
	FragTrap frag3("FT-003");
	frag3 = frag;

	std::cout << "\n=== Destructors ===" << std::endl;
	return (0);
}
