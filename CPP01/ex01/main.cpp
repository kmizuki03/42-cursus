/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:16:42 by kmizuki           #+#    #+#             */
/*   Updated: 2026/04/21 17:09:10 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    int n = 3;
	int i=0;
    Zombie* horde = zombieHorde(n, "HordeZombie");

	while(i<n)
	{
		horde[i].announce();
		i++;
	}

    delete[] horde;

    return 0;
}
