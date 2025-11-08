/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:29:57 by kmizuki           #+#    #+#             */
/*   Updated: 2025/09/22 18:10:51 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	update_zoom(t_fractal *f, double mouse_re, double mouse_im,
		double zoom_factor)
{
	double	new_zoom;

	new_zoom = f->zoom * zoom_factor;
	f->offset_x = mouse_re + (f->offset_x - mouse_re) / zoom_factor;
	f->offset_y = mouse_im + (f->offset_y - mouse_im) / zoom_factor;
	f->zoom = new_zoom;
}

void	handle_zoom(t_fractal *f, int button, int x, int y)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mouse_re = (x - WIDTH / 2.0) / (0.5 * f->zoom * WIDTH) + f->offset_x;
	mouse_im = (y - HEIGHT / 2.0) / (0.5 * f->zoom * HEIGHT) + f->offset_y;
	if (button == ZOOM_IN)
		zoom_factor = 1.1;
	else if (button == ZOOM_OUT)
		zoom_factor = 0.9;
	else
		return ;
	update_zoom(f, mouse_re, mouse_im, zoom_factor);
}
