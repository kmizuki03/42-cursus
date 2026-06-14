/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:21:41 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:11:14 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = "HelloWorld";
// 	char	str2[] = "HelloWorld";
// 	int		i;

// 	i = 0;
// 	while (str1[i])
// 	{
// 		str1[i] = ft_toupper(str1[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (str2[i])
// 	{
// 		str2[i] = toupper(str2[i]);
// 		i++;
// 	}
// 	printf("After ft_toupper: %s\n", str1);
// 	printf("After toupper:    %s\n", str2);
// 	return (0);
// }
