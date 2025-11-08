/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:53:50 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/14 16:37:22 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile t_clstate	g_cl = {0, 0, 0};

static void	on_sig(int sig)
{
	if (sig == SIGUSR1)
		g_cl.ack = 1;
	else if (sig == SIGUSR2)
		g_cl.done = 1;
	else if (sig == SIGALRM)
		g_cl.timeout = 1;
}

int	setup_client_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = on_sig;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
	{
		ft_putstr_fd("sigaction error\n", 2);
		return (1);
	}
	if (sigaction(SIGALRM, &sa, 0) == -1)
	{
		ft_putstr_fd("sigaction error\n", 2);
		return (1);
	}
	return (0);
}
