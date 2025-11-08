/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:44:24 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:58:41 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	data1[] = "HelloWorld";
// 	char	data2[] = "HelloEarth";
// 	int		res1;
// 	int		res2;

// 	res1 = ft_memcmp(data1, data2, 5);
// 	res2 = memcmp(data1, data2, 5);
// 	printf("After ft_memcmp: %d\n", res1);
// 	printf("After memcmp:    %d\n", res2);
// 	return (0);
// }
