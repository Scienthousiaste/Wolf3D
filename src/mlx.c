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
	(void)mlx;
}

void	new_window_image(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx,
		mlx->window_width, mlx->window_height);
	if (mlx->img_ptr == NULL)
	{
		ft_putstr_fd("failed to create image\n", 2);
		exit(1);
	}
	mlx->window_image = mlx->img_ptr->pixels;
	mlx->img_size_line = mlx->window_width * 4;
	mlx_image_to_window(mlx->mlx, mlx->img_ptr, 0, 0);
}

void	close_program(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	mlx_close_window(mlx->mlx);
}
