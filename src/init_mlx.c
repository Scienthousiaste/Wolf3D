/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:33:38 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 18:55:52 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_mlx_struct(t_wolf *wolf)
{
	t_map *map;
	t_mlx *mlx;

	map = &wolf->map;
	mlx = &wolf->mlx;
	ft_bzero((void *)mlx, sizeof(mlx));
	mlx->window_name = "Wolf3D";
	mlx->window_width = WIN_WIDTH;
	mlx->window_height = WIN_HEIGHT;
	map->offset_y = 0;
	map->offset_x = 0;
	map->line_size = (mlx->img_size_line / 4);
	map->square_side = DEFAULT_SQUARE_SIDE;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->connect = mlx_init();
	if (mlx->connect == NULL)
	{
		ft_putstr_fd("connection failed::: mlx_init() failed\n", 2);
		exit(1);
	}
}
