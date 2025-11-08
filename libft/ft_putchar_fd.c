/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:51:26 by kmizuki           #+#    #+#             */
/*   Updated: 2025/04/30 15:58:07 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
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
// 	ft_putchar_fd('A', fd);
// 	ft_putchar_fd('\n', fd);
// 	close(fd);
// 	return (0);
// }
