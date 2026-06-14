/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:13:21 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 19:18:12 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h>

// int	main(void)
// {
// 	char	str1[10] = "abcdefghi";
// 	char	str2[10] = "abcdefghi";

// 	ft_bzero(str1, 5);
// 	printf("After ft_bzero: %s\n", str1);
// 	bzero(str2, 5);
// 	printf("After bzero:    %s\n", str2);
// 	return (0);
// }
