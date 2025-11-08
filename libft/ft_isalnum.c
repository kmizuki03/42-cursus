/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:54:57 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 18:57:34 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_isalnum('A') = %d\n", ft_isalnum('A'));
// 	printf("ft_isalnum('z') = %d\n", ft_isalnum('z'));
// 	printf("ft_isalnum('5') = %d\n", ft_isalnum('5'));
// 	printf("ft_isalnum('@') = %d\n", ft_isalnum('@'));
// 	printf("ft_isalnum(' ') = %d\n", ft_isalnum(' '));
// 	printf("ft_isalnum(-1)  = %d\n", ft_isalnum(-1));
// 	return (0);
// }
