/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:18 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/13 15:59:48 by jmurte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	*meow_thread(void)
{
	system("afplay ./sounds/cat.wav");
	pthread_exit(NULL);
}

void	open_window(t_mlx *mlx)
{
	mlx->window = mlx_new_window(mlx->connect, mlx->window_width,
		mlx->window_height, mlx->window_name);
	if (mlx->window == NULL)
	{
		ft_putstr_fd("connection failed::: mlx_new_window() failed\n", 2);
	}
}

void	new_window_image(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->connect,
		mlx->window_width, mlx->window_height);
	mlx->window_image = (int *)mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
		&mlx->img_size_line, &mlx->endian);
}

int		close_program(t_mlx *mlx)
{
	(void)mlx;
	exit(1);
}
