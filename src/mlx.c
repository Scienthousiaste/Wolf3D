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

void	play_attack_sound(void)
{
	platform_play_sound("./sounds/cat.wav");
}

void	open_window(t_mlx *mlx)
{
	(void)mlx;
}

void	new_window_image(t_mlx *mlx)
{
	mlx->window_image = platform_get_framebuffer(mlx->platform);
	if (mlx->window_image == NULL)
	{
		ft_putstr_fd("failed to get framebuffer\n", 2);
		exit(1);
	}
	mlx->img_size_line = mlx->window_width * 4;
}

void	close_program(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	platform_request_close(mlx->platform);
}
