/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/19 14:31:41 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key(int keycode, t_fractal *f)
{
	if (keycode == ESC)
		handle_close(f);
	else if (keycode == LEFT || keycode == RIGHT || keycode == UP
		|| keycode == DOWN)
	{
		if (keycode == LEFT)
			f->offset_x -= 0.1 / f->zoom;
		else if (keycode == RIGHT)
			f->offset_x += 0.1 / f->zoom;
		else if (keycode == UP)
			f->offset_y -= 0.1 / f->zoom;
		else if (keycode == DOWN)
			f->offset_y += 0.1 / f->zoom;
		draw_fractal(f);
	}
	return (0);
}
