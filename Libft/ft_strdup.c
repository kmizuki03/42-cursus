/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:47:02 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/28 17:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	i = 0;
	while (s1[len] != '\0')
		len++;
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*original = "Hello World!";
// 	char		*dup1;
// 	char		*dup2;

// 	dup1 = ft_strdup(original);
// 	dup2 = strdup(original);
// 	printf("After ft_strdup: %s\n", dup1);
// 	printf("After strdup:    %s\n", dup2);
// 	free(dup1);
// 	free(dup2);
// 	return (0);
// }
