/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:22 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:28:22 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	buffer[2];
	int		bytes;
	char	*tmp;

	if (fd < 0)
		return (NULL);
	line = ft_strdup("");
	bytes = read(fd, buffer, 1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
		if (buffer[0] == '\n')
			break ;
		bytes = read(fd, buffer, 1);
	}
	if (bytes <= 0 && (!line || line[0] == '\0'))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int finish)
{
	char	*word;
	int		i;

	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	fill_words(char **result, char const *s, char c)
{
	size_t	i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			result[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	result[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	fill_words(result, s, c);
	return (result);
}
