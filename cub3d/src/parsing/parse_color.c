/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 14:10:00 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 14:10:00 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	is_valid_number(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_color(t_color *color, char *line)
{
	char	**rgb;
	int		ok;

	trim_newline(line);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);
	ok = (rgb[0] && rgb[1] && rgb[2] && !rgb[3] && is_valid_number(rgb[0])
			&& is_valid_number(rgb[1]) && is_valid_number(rgb[2]));
	if (ok)
	{
		color->r = ft_atoi(rgb[0]);
		color->g = ft_atoi(rgb[1]);
		color->b = ft_atoi(rgb[2]);
	}
	free_split(rgb);
	if (!ok || color->r < 0 || color->r > 255 || color->g < 0
		|| color->g > 255 || color->b < 0 || color->b > 255)
		return (1);
	return (0);
}

int	set_texture(t_game *game, int idx, char *val)
{
	if (!val || game->config.tex_set[idx])
		return (-1);
	game->config.tex_path[idx] = ft_strdup(val);
	if (!game->config.tex_path[idx])
		return (-1);
	game->config.tex_set[idx] = 1;
	return (0);
}

int	set_color(t_color *color, int *set, char *val)
{
	if (!val || *set)
		return (-1);
	if (parse_color(color, val))
		return (-1);
	*set = 1;
	return (0);
}
