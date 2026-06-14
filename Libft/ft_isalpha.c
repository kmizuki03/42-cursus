/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:35:49 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/25 18:46:15 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test1;
// 	char	test2;
// 	char	test3;
// 	char	test4;

// 	test1 = 'A';
// 	test2 = 'z';
// 	test3 = '5';
// 	test4 = '#';
// 	printf("ft_isalpha('%c') = %d\n", test1, ft_isalpha(test1));
// 	printf("ft_isalpha('%c') = %d\n", test2, ft_isalpha(test2));
// 	printf("ft_isalpha('%c') = %d\n", test3, ft_isalpha(test3));
// 	printf("ft_isalpha('%c') = %d\n", test4, ft_isalpha(test4));
// 	return (0);
// }
