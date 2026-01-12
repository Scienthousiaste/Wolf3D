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

	color = red << 24;
	color += green << 16;
	color += blue << 8;
	color += 0xFF;
	return (color);
}

static void	put_pixel_raw(t_mlx *mlx, int x, int y, int color)
{
	int		idx;

	if (x < 0 || x >= mlx->window_width || y < 0 || y >= mlx->window_height)
		return ;
	idx = (y * mlx->window_width + x) * 4;
	mlx->window_image[idx + 0] = (color >> 24) & 0xFF;
	mlx->window_image[idx + 1] = (color >> 16) & 0xFF;
	mlx->window_image[idx + 2] = (color >> 8) & 0xFF;
	mlx->window_image[idx + 3] = color & 0xFF;
}

void		draw_square(t_mlx *mlx, t_point *begin,
			size_t square_side, int color)
{
	size_t		j;
	size_t		i;

	i = -1;
	while (++i < square_side)
	{
		j = -1;
		while (++j < square_side)
		{
			put_pixel_raw(mlx, (int)begin->x + j, (int)begin->y + i, color);
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
	int		idx;
	int		color;

	if (p.x < 0 || p.x >= mlx->window_width || p.y < 0 || p.y >= mlx->window_height)
		return (0);
	idx = (p.y * mlx->window_width + p.x) * 4;
	color = mlx->window_image[idx] << 24;
	color += mlx->window_image[idx + 1] << 16;
	color += mlx->window_image[idx + 2] << 8;
	color += mlx->window_image[idx + 3];
	return (color);
}

void		put_pixel_image(t_mlx *mlx, t_pixel p, int color)
{
	put_pixel_raw(mlx, p.x, p.y, color);
}
