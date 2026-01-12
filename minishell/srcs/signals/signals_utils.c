/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:40 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:41 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct sigaction	*get_old_int(void)
{
	static struct sigaction	old_int;

	return (&old_int);
}

static struct sigaction	*get_old_quit(void)
{
	static struct sigaction	old_quit;

	return (&old_quit);
}

void	setup_parent_wait_signals(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, get_old_int());
	sigaction(SIGQUIT, &sa_ignore, get_old_quit());
}

void	restore_parent_signals(void)
{
	sigaction(SIGINT, get_old_int(), NULL);
	sigaction(SIGQUIT, get_old_quit(), NULL);
}
