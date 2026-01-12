/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/14 00:00:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*do_tilde_expand(char *expanded, char *value, t_shell *shell)
{
	char	*home;
	char	*result;

	if (expanded[0] != '~' || is_quoted_str(value))
		return (expanded);
	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (expanded);
	if (expanded[1] == '\0')
	{
		free(expanded);
		return (ft_strdup(home));
	}
	if (expanded[1] == '/')
	{
		result = ft_strjoin(home, expanded + 1);
		free(expanded);
		return (result);
	}
	return (expanded);
}

static void	handle_wildcard_word(char **av, int *idx, char *word)
{
	char	**wildcard_exp;
	int		j;

	wildcard_exp = expand_wildcard(word);
	free(word);
	if (wildcard_exp)
	{
		j = 0;
		while (wildcard_exp[j])
			av[(*idx)++] = wildcard_exp[j++];
		free(wildcard_exp);
	}
}

static int	process_unquoted(char **av, int *idx, char *expanded, t_token **t)
{
	char	**words;
	int		i;

	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (-1);
	i = 0;
	while (words[i])
	{
		if (has_wildcard(words[i]))
			handle_wildcard_word(av, idx, words[i]);
		else if (words[i][0] != '\0')
			av[(*idx)++] = words[i];
		else
			free(words[i]);
		i++;
	}
	free(words);
	*t = (*t)->next;
	return (0);
}

int	process_word_token(t_token **t, char **av, int *idx, t_shell *s)
{
	char	*expanded;
	int		quoted;

	quoted = is_quoted_str((*t)->value);
	expanded = expand_variables((*t)->value, s);
	if (!expanded)
		return (-1);
	expanded = do_tilde_expand(expanded, (*t)->value, s);
	if (!expanded)
		return (-1);
	if (quoted)
	{
		av[(*idx)++] = expanded;
		*t = (*t)->next;
		return (0);
	}
	return (process_unquoted(av, idx, expanded, t));
}
