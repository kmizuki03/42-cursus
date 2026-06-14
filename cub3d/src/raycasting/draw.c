/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:39 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:50:23 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_wall_tex_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (TEX_EAST);
		return (TEX_WEST);
	}
	if (ray->step_y > 0)
		return (TEX_SOUTH);
	return (TEX_NORTH);
}

static int	calc_tex_x(t_ray *ray, t_img *tex)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (ray->side == 0 && ray->dir.x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static int	clamp_tex_y(double tex_pos, int tex_height)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	return (tex_y);
}

void	draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
	int		tex_index;
	int		tex_x;
	int		y;
	double	step;
	double	tex_pos;

	tex_index = get_wall_tex_index(ray);
	tex_x = calc_tex_x(ray, &game->textures[tex_index]);
	step = 1.0 * game->textures[tex_index].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		img_pixel_put(&game->screen, x, y,
			get_tex_color(&game->textures[tex_index], tex_x,
				clamp_tex_y(tex_pos, game->textures[tex_index].height)));
		tex_pos += step;
		y++;
	}
}
