/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/19 15:45:55 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_quoted_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1 || str[i] == 2 || str[i] == 3 || str[i] == 4)
			return (1);
		i++;
	}
	return (0);
}

static char	*process_wildcard_redir(char *filename, char *value, t_shell *sh)
{
	char	**expanded;
	char	*result;

	expanded = expand_wildcard(filename);
	if (!expanded || !expanded[0] || expanded[1] != NULL)
	{
		print_error(value, NULL, "ambiguous redirect");
		if (expanded)
			free_array(expanded);
		sh->last_exit_status = 1;
		return (NULL);
	}
	result = ft_strdup(expanded[0]);
	free_array(expanded);
	return (result);
}

static char	*expand_redir_filename(t_token **tok, t_shell *sh)
{
	char	*filename;
	int		quoted;

	quoted = is_quoted_redir((*tok)->value);
	filename = expand_variables((*tok)->value, sh);
	if (!filename)
		return (NULL);
	if (!quoted && is_ambiguous_redirect(filename))
	{
		print_error((*tok)->value, NULL, "ambiguous redirect");
		free(filename);
		sh->last_exit_status = 1;
		return (NULL);
	}
	if (has_wildcard(filename) && !quoted)
	{
		filename = process_wildcard_redir(filename, (*tok)->value, sh);
		if (!filename)
			return (NULL);
	}
	return (filename);
}

char	*get_redir_filename_bonus(t_token **tok, t_shell *sh, t_redir_type type)
{
	if (type == REDIR_HEREDOC)
		return (remove_markers((*tok)->value));
	return (expand_redir_filename(tok, sh));
}
