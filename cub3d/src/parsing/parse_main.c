/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:18 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:28:18 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_cub_file(t_game *game, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error(ERR_FILE));
	if (parse_config(game, fd))
	{
		close(fd);
		return (ft_error(ERR_FORMAT));
	}
	if (parse_map(game, fd))
	{
		close(fd);
		return (ft_error(ERR_MAP));
	}
	close(fd);
	if (validate_map(game))
		return (1);
	return (0);
}
