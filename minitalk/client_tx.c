/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_tx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:54:06 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/14 16:42:50 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern volatile t_clstate	g_cl;

static int	send_bit(pid_t pid, int bit)
{
	if (bit)
	{
		if (kill(pid, SIGUSR2) == -1)
			return (-1);
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
			return (-1);
	}
	return (0);
}

static int	wait_ack_with_timeout(void)
{
	g_cl.timeout = 0;
	alarm(1);
	while (!g_cl.ack && !g_cl.timeout)
		pause();
	alarm(0);
	if (g_cl.timeout)
		return (-1);
	g_cl.ack = 0;
	return (0);
}

static int	send_char(pid_t pid, unsigned char c)
{
	int	bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (send_bit(pid, bit) == -1)
			return (-1);
		if (wait_ack_with_timeout() == -1)
			return (-1);
		i--;
	}
	return (0);
}

int	send_msg(pid_t pid, const char *msg)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(msg);
	while (i <= len)
		if (send_char(pid, (unsigned char)msg[i++]) == -1)
			return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_putstr_fd("Usage: client <server_pid> <message>\n", 2);
		return (1);
	}
	if (setup_client_signals() != 0)
		return (1);
	pid = ft_atoi(av[1]);
	if (pid <= 1)
	{
		ft_putstr_fd("Bad PID\n", 2);
		return (1);
	}
	if (send_msg(pid, av[2]) == -1)
	{
		ft_putstr_fd("Send error\n", 2);
		return (1);
	}
	while (!g_cl.done)
		pause();
	ft_putstr_fd("Message delivered!\n", 1);
	return (0);
}
