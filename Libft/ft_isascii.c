/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:58:15 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 19:04:13 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_isascii(0)    = %d\n", ft_isascii(0));
// 	printf("ft_isascii(127)  = %d\n", ft_isascii(127));
// 	printf("ft_isascii(128)  = %d\n", ft_isascii(128));
// 	printf("ft_isascii(-1)   = %d\n", ft_isascii(-1));
// 	printf("ft_isascii('A')  = %d\n", ft_isascii('A'));
// 	printf("ft_isascii(255)  = %d\n", ft_isascii(255));
// 	return (0);
// }
