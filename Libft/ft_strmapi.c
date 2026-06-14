/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:07:47 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/29 18:05:50 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	result = malloc(ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

// char	to_upper_odd(unsigned int i, char c)
// {
// 	if (i % 2 == 1 && c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// 	const char	*str = "libft is fun!";
// 	char		*result;

// 	if ((result = ft_strmapi(str, to_upper_odd)))
// 	{
// 		printf("%s\n", result);
// 		free(result);
// 	}
// 	return (0);
// }
