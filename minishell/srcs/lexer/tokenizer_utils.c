/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:22 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:23 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&'
		|| c == '(' || c == ')' || c == ';');
}

static void	print_unclosed_quote_error(char quote)
{
	write(2, "minishell: unexpected EOF while looking for matching `", 54);
	write(2, &quote, 1);
	write(2, "'\n", 2);
}

char	*handle_quoted(char *input, int *i, char quote)
{
	int		start;
	char	*value;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (print_unclosed_quote_error(quote), NULL);
	value = ft_substr(input, start, *i - start);
	(*i)++;
	return (value);
}

char	*join_markers(char *ret, char *part, char m_start, char m_end)
{
	char	*tmp;
	char	markers[2];

	markers[1] = '\0';
	markers[0] = m_start;
	tmp = ret;
	ret = ft_strjoin(ret, markers);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(ret, part);
	free(tmp);
	markers[0] = m_end;
	tmp = ret;
	ret = ft_strjoin(ret, markers);
	free(tmp);
	return (ret);
}
