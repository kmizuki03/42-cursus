/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:51 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:51:42 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_tex_color(t_img *tex, int x, int y)
{
	char	*src;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	src = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

static int	load_single_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (ft_error(ERR_TEXTURE));
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!tex->addr)
		return (ft_error(ERR_TEXTURE));
	return (0);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (!game->config.tex_path[i])
			return (ft_error(ERR_TEXTURE));
		if (load_single_texture(game,
				&game->textures[i], game->config.tex_path[i]))
			return (1);
		i++;
	}
	return (0);
}
