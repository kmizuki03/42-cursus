/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:01:57 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 19:04:01 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_isprint(31)   = %d\n", ft_isprint(31));
// 	printf("ft_isprint(32)   = %d\n", ft_isprint(32));
// 	printf("ft_isprint(65)   = %d\n", ft_isprint(65));
// 	printf("ft_isprint(126)  = %d\n", ft_isprint(126));
// 	printf("ft_isprint(127)  = %d\n", ft_isprint(127));
// 	printf("ft_isprint(-1)   = %d\n", ft_isprint(-1));
// 	return (0);
// }
