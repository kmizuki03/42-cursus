/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:08:30 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/30 16:09:57 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	nb = nb % 10;
	c = nb + '0';
	write(fd, &c, 1);
}

// #include "libft.h"
// #include <fcntl.h>

// int	main(void)
// {
// 	int	fd;

// 	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (1);
// 	ft_putnbr_fd(12345, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(-9876, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(0, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(-2147483648, fd);
// 	close(fd);
// 	return (0);
// }
