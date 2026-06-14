/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/14 00:00:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_heredoc_warning(char *delimiter)
{
	write(2, "minishell: warning: ", 20);
	write(2, "here-document at line 1 delimited by end-of-file (wanted `", 58);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
}
