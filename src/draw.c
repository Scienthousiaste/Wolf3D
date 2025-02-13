/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:05:36 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/05 18:06:31 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			set_rgb(int red, int green, int blue)
{
	int		color;

	color = red << 16;
	color += green << 8;
	color += blue;
	return (color);
}

void		draw_square(t_mlx *mlx, t_point *begin,
			size_t square_side, int color)
{
	size_t		j;
	size_t		i;
	int			line_size;

	i = -1;
	line_size = (mlx->img_size_line / 4);
	while (++i < square_side)
	{
		j = -1;
		while (++j < square_side)
		{
			mlx->window_image[((int)i + (int)begin->y) * line_size
				+ ((int)j + (int)begin->x)] = color;
		}
	}
}

int			is_ground_pixel(t_wolf *wolf, t_pixel p)
{
	t_pixel pp;

	pp.x = p.x;
	if (p.y + 1 == wolf->mlx.window_height)
		return (1);
	pp.y = (p.y + 1 < wolf->mlx.window_height) ?
		p.y + 1 : p.y;
	return (get_pixel_window(&wolf->mlx, pp) == wolf->color_ground);
}

int			get_pixel_window(t_mlx *mlx, t_pixel p)
{
	return (mlx->window_image[p.x + p.y * (mlx->img_size_line / 4)]);
}

void		put_pixel_image(t_mlx *mlx, t_pixel p, int color)
{
	mlx->window_image[p.x + p.y * (mlx->img_size_line / 4)] = color;
}
