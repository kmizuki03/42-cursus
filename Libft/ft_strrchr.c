/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:20:05 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/26 13:31:28 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last = (char *)(s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (last);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[] = "HelloWorld";
// 	char	*res1;
// 	char	*res2;

// 	res1 = ft_strrchr(str, 'l');
// 	res2 = strrchr(str, 'l');
// 	printf("After ft_strrchr: %s\n", res1);
// 	printf("After strrchr:    %s\n", res2);
// 	return (0);
// }
