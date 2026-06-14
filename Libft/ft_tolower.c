/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:35:21 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:11:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int	main(void)
// {
// 	char	str1[] = "HelloWorld";
// 	char	str2[] = "HelloWorld";
// 	int		i;

// 	i = 0;
// 	while (str1[i])
// 	{
// 		str1[i] = ft_tolower(str1[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (str2[i])
// 	{
// 		str2[i] = tolower(str2[i]);
// 		i++;
// 	}
// 	printf("After ft_tolower: %s\n", str1);
// 	printf("After tolower:    %s\n", str2);
// 	return (0);
// }
