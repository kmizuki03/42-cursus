/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:39:35 by kato              #+#    #+#             */
/*   Updated: 2025/10/14 16:37:22 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_svstate
{
	volatile sig_atomic_t	bitc;
	volatile sig_atomic_t	acc;
	volatile sig_atomic_t	cli;
}							t_svstate;

typedef struct s_clstate
{
	volatile sig_atomic_t	ack;
	volatile sig_atomic_t	done;
	volatile sig_atomic_t	timeout;
}							t_clstate;

size_t						ft_strlen(const char *s);
void						ft_putstr_fd(const char *s, int fd);
void						ft_putnbr_fd(pid_t n, int fd);
int							ft_atoi(const char *s);

void						sv_on_sig(int sig, siginfo_t *info, void *ctx);

int							setup_client_signals(void);
int							send_msg(pid_t pid, const char *msg);

#endif
