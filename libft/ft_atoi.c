/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:10:27 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 14:16:54 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;
// 	int		res1;
// 	int		res2;

// 	str1 = "   -1234abc";
// 	str2 = "   +5678def";
// 	res1 = ft_atoi(str1);
// 	res2 = atoi(str1);
// 	printf("After ft_atoi: %d\n", res1);
// 	printf("After atoi:    %d\n", res2);
// 	res1 = ft_atoi(str2);
// 	res2 = atoi(str2);
// 	printf("After ft_atoi: %d\n", res1);
// 	printf("After atoi:    %d\n", res2);
// 	return (0);
// }
