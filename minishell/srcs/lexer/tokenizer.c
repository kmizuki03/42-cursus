/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:24 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:25 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_unquoted(char **ret, char *input, int *i)
{
	char	*part;
	char	*tmp;
	int		start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_meta(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	part = ft_substr(input, start, *i - start);
	tmp = *ret;
	*ret = ft_strjoin(*ret, part);
	free(tmp);
	free(part);
}

static char	*handle_quote_part(char *input, int *i, char **ret)
{
	char	*part;
	char	quote_char;

	quote_char = input[*i];
	part = handle_quoted(input, i, quote_char);
	if (!part)
		return (free(*ret), NULL);
	if (quote_char == '\'')
		*ret = join_markers(*ret, part, 1, 2);
	else
		*ret = join_markers(*ret, part, 3, 4);
	free(part);
	return (*ret);
}

static char	*extract_word(char *input, int *i)
{
	char	*ret;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	while (input[*i] && !ft_isspace(input[*i]) && !is_meta(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!handle_quote_part(input, i, &ret))
				return (NULL);
		}
		else
			append_unquoted(&ret, input, i);
	}
	return (ret);
}

static t_token	*process_token(char *input, int *i)
{
	char	*word;
	t_token	*new;

	if (is_meta(input[*i]))
		return (handle_operator(input, i));
	word = extract_word(input, i);
	if (!word)
		return (NULL);
	new = new_token(TOKEN_WORD, word);
	free(word);
	return (new);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_token	*new;
	int		i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '#' || !input[i])
			break ;
		new = process_token(input, &i);
		if (!new)
			return (free_tokens(tokens), NULL);
		if (new->type == TOKEN_EOF)
			return (free_token(new), free_tokens(tokens), NULL);
		add_token(&tokens, new);
	}
	return (tokens);
}
