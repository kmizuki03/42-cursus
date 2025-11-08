/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:32:01 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:38:10 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	int		res1;
// 	int		res2;

// 	s1 = "HelloWorld";
// 	s2 = "HelloEarth";
// 	res1 = ft_strncmp(s1, s2, 6);
// 	res2 = strncmp(s1, s2, 6);
// 	printf("After ft_strncmp: %d\n", res1);
// 	printf("After strncmp:    %d\n", res2);
// 	return (0);
// }
