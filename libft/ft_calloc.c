/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:20:56 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 15:37:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total;
	unsigned char	*ptr;
	size_t			i;

	total = count * size;
	if (size != 0 && total / size != count)
		return (NULL);
	ptr = malloc(total);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	int	*i;
// 	int	n;
// 	int	j;

// 	n = 5;
// 	i = (int *)ft_calloc(n, sizeof(int));
// 	if (!i)
// 	{
// 		printf("calloc failed\n");
// 		return (1);
// 	}
// 	for (j = 0; j < n; j++)
// 		printf("i[%d] = %d\n", j, i[j]);
// 	free(i);
// 	return (0);
// }
