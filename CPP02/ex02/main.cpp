/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:33:22 by kmizuki           #+#    #+#             */
/*   Updated: 2026/05/19 13:33:23 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	std::cout << "\n=== Additional tests ===" << std::endl;

	Fixed c(10);
	Fixed d(20.5f);

	std::cout << "c (10) < d (20.5): " << (c < d) << std::endl;
	std::cout << "c (10) > d (20.5): " << (c > d) << std::endl;
	std::cout << "c (10) == d (20.5): " << (c == d) << std::endl;
	std::cout << "c (10) != d (20.5): " << (c != d) << std::endl;

	std::cout << "\nArithmetic operations:" << std::endl;
	std::cout << "c + d = " << c + d << std::endl;
	std::cout << "d - c = " << d - c << std::endl;
	std::cout << "c * d = " << c * d << std::endl;
	std::cout << "d / c = " << d / c << std::endl;

	std::cout << "\nmin/max tests:" << std::endl;
	std::cout << "min(c, d) = " << Fixed::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << Fixed::max(c, d) << std::endl;

	return 0;
}
