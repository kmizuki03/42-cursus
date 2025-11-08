/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:39:57 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:58:30 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	data[] = "HelloWorld";
// 	void	*res1;
// 	void	*res2;

// 	res1 = ft_memchr(data, 'o', 10);
// 	res2 = memchr(data, 'o', 10);
// 	printf("After ft_memchr: %s\n", (char *)res1);
// 	printf("After memchr:    %s\n", (char *)res2);
// 	return (0);
// }
