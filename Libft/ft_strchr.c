/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:14:06 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:39:15 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[] = "HelloWorld";
// 	char	*res1;
// 	char	*res2;

// 	res1 = ft_strchr(str, 'o');
// 	res2 = strchr(str, 'o');
// 	printf("After ft_strchr: %s\n", res1);
// 	printf("After strchr:    %s\n", res2);
// 	return (0);
// }
