/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:36:49 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:09:04 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst == src || len == 0)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len != 0)
		{
			len--;
			((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str1[20] = "HelloWorld";
// 	char	str2[20] = "HelloWorld";

// 	ft_memmove(str1 + 2, str1, 5);
// 	printf("After ft_memmove: %s\n", str1);
// 	memmove(str2 + 2, str2, 5);
// 	printf("After memmove:    %s\n", str2);
// 	return (0);
// }
