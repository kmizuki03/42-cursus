/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:47:17 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 18:54:08 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_isdigit('0') = %d\n", ft_isdigit('0')); // → 1
// 	printf("ft_isdigit('5') = %d\n", ft_isdigit('5')); // → 1
// 	printf("ft_isdigit('9') = %d\n", ft_isdigit('9')); // → 1
// 	printf("ft_isdigit('a') = %d\n", ft_isdigit('a')); // → 0
// 	printf("ft_isdigit(' ') = %d\n", ft_isdigit(' ')); // → 0
// 	printf("ft_isdigit(-1)  = %d\n", ft_isdigit(-1));  // → 0
// 	printf("ft_isdigit(200) = %d\n", ft_isdigit(200)); // → 0
// 	return (0);
// }
