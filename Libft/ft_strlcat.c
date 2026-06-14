/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:40:18 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:08:47 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && i + j + 1 < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	while (src[j] != '\0')
		j++;
	return (i + j);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[20] = "Hello";
// 	size_t	len1;

// 	len1 = ft_strlcat(str1, "World", sizeof(str1));
// 	printf("After ft_strlcat: %s (%zu)\n", str1, len1);
// 	return (0);
// }
