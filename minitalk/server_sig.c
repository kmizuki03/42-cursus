/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:49:59 by kato              #+#    #+#             */
/*   Updated: 2025/10/03 17:03:27 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern volatile t_svstate	g_sv;

static void	reset_state(void)
{
	g_sv.bitc = 0;
	g_sv.acc = 0;
}

static void	begin_client(pid_t pid)
{
	if (pid != g_sv.cli && g_sv.bitc != 0)
		reset_state();
	g_sv.cli = pid;
}

static int	append_bit(int is_one)
{
	g_sv.acc = ((g_sv.acc << 1) | (is_one != 0)) & 0xFF;
	return (++g_sv.bitc == 8);
}

static int	handle_byte(unsigned char ch)
{
	if (ch == 0)
	{
		write(1, "\n", 1);
		reset_state();
		if (g_sv.cli > 1)
		{
			kill(g_sv.cli, SIGUSR1);
			kill(g_sv.cli, SIGUSR2);
		}
		return (1);
	}
	write(1, &ch, 1);
	reset_state();
	return (0);
}

void	sv_on_sig(int sig, siginfo_t *info, void *ctx)
{
	(void)ctx;
	begin_client(info->si_pid);
	if (append_bit(sig == SIGUSR2))
		if (handle_byte((unsigned char)g_sv.acc))
			return ;
	if (g_sv.cli > 1)
		kill(g_sv.cli, SIGUSR1);
}
