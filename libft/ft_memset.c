/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:08:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:39:01 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str1[10] = "abcdefghi";
// 	char	str2[10] = "abcdefghi";

// 	ft_memset(str1, 'X', 5);
// 	printf("After ft_memset: %s\n", str1);
// 	memset(str2, 'X', 5);
// 	printf("After memset:    %s\n", str2);
// 	return (0);
// }
