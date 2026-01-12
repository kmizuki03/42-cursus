/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/12 00:00:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_matches(char **result, int count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < count - 1)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strcmp(result[i], result[j]) > 0)
				swap_strings(&result[i], &result[j]);
		}
	}
}

char	**create_single_result(char *pattern)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(pattern);
	result[1] = NULL;
	return (result);
}

char	**init_result_array(int count, DIR **dir)
{
	char	**result;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	*dir = opendir(".");
	if (!*dir)
		return (free(result), NULL);
	return (result);
}
