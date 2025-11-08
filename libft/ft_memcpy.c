/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:29:02 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 19:33:08 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	src[] = "Hello42";
// 	char	dst1[10] = "abcdefghi";
// 	char	dst2[10] = "abcdefghi";

// 	ft_memcpy(dst1, src, 5);
// 	printf("After ft_memcpy: %s\n", dst1);
// 	memcpy(dst2, src, 5);
// 	printf("After memcpy:    %s\n", dst2);
// 	return (0);
// }
