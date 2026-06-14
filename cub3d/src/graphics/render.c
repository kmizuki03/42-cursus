/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:51 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:51:35 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_row(t_img *img, int y, int color)
{
	unsigned int	*row;
	int				x;

	row = (unsigned int *)(img->addr + y * img->line_length);
	x = 0;
	while (x < img->width)
		row[x++] = color;
}

void	draw_ceiling_floor(t_game *game)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_int(game->config.ceiling);
	floor_color = rgb_to_int(game->config.floor);
	y = 0;
	while (y < WIN_HEIGHT / 2)
		fill_row(&game->screen, y++, ceiling_color);
	while (y < WIN_HEIGHT)
		fill_row(&game->screen, y++, floor_color);
}

int	render_frame(t_game *game)
{
	draw_ceiling_floor(game);
	perform_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}
