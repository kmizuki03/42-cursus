/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:04:48 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 19:17:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_strlen(\"\")        = %zu\n", ft_strlen(""));
// 	printf("ft_strlen(\"Hello\")    = %zu\n", ft_strlen("Hello"));
// 	printf("ft_strlen(\"42Tokyo\")  = %zu\n", ft_strlen("42Tokyo"));
// 	printf("ft_strlen(\" \")        = %zu\n", ft_strlen(" "));
// 	printf("ft_strlen(\"abc\\0def\") = %zu\n", ft_strlen("abc\0def"));
// 	return (0);
// }
