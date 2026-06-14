/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:37:33 by kato              #+#    #+#             */
/*   Updated: 2025/10/15 15:15:54 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

static void	put_unsigned_fd(unsigned long x, int fd)
{
	char	b[32];
	int		i;

	i = 31;
	while (x)
	{
		b[i--] = '0' + (x % 10);
		x /= 10;
	}
	write(fd, b + i + 1, 31 - i);
}

void	ft_putnbr_fd(pid_t n, int fd)
{
	long	x;

	x = n;
	if (x == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (x < 0)
	{
		write(fd, "-", 1);
		x = -x;
	}
	put_unsigned_fd((unsigned long)x, fd);
}

int	ft_atoi(const char *s)
{
	long	n;
	int		i;
	int		sg;

	i = 0;
	sg = 1;
	n = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sg = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return ((int)(n * sg));
}
