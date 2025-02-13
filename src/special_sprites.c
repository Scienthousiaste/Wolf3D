/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:38:09 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/13 16:41:19 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		sprite_too_big(t_wolf *wolf, int offset_x, int offset_y, t_img *sprite)
{
	if ((offset_x + sprite->width) >= wolf->mlx.window_width
		|| (offset_x + sprite->width) < 0
		|| (offset_y + sprite->height) < 0
		|| (offset_y + sprite->height) >= wolf->mlx.window_height)
		return (1);
	return (0);
}

void	put_cat_arm_in_img(t_wolf *wolf, t_img *sprite,
		int offset_x, int offset_y)
{
	int line;
	int col;
	int color;

	col = 0;
	while (col < sprite->height && col + offset_y <= wolf->mlx.window_height)
	{
		line = 0;
		while (line < sprite->width && line + offset_x
				<= wolf->mlx.window_width)
		{
			color = sprite->img_ptr[sprite->size_line / 4 * col + line];
			if (color != COLOR_TRANSPARENT)
			{
				put_pixel_image(&wolf->mlx, make_pixel(line + offset_x,
							col + offset_y), color);
			}
			line++;
		}
		col++;
	}
}

void	draw_cat_arm_sprite(t_wolf *wolf, t_img *sprite)
{
	int			offset_x;
	int			offset_y;
	static int	j = 10;
	static int	i = 40;

	offset_x = wolf->mlx.window_width - sprite->width - i;
	offset_y = wolf->mlx.window_height - sprite->height - sprite->height + j;
	if (i < 480)
	{
		if (sprite_too_big(wolf, offset_x, offset_y, sprite))
			ft_putstr_fd("Error, arm sprite is too big for the window size\n",
			2);
		else
			put_cat_arm_in_img(wolf, sprite, offset_x, offset_y);
	}
	else
	{
		wolf->player.is_attacking = FALSE;
		i = 40;
		j = 10;
		return ;
	}
	i += 40;
	j += 10;
}

void	put_cat_legs_in_img(t_wolf *wolf, t_img *sprite)
{
	t_pixel	offset;
	int		line;
	int		col;
	int		color;

	col = -1;
	offset.x = wolf->mlx.window_width / 2 - 200;
	offset.y = wolf->mlx.window_height - 200;
	if (sprite_too_big(wolf, offset.x, offset.y, sprite))
	{
		ft_putstr_fd("Error, one sprite is too big for the window size\n", 2);
		return ;
	}
	while (++col < sprite->height && col + offset.y <= wolf->mlx.window_height)
	{
		line = -1;
		while (++line < sprite->width && line + offset.x
				<= wolf->mlx.window_width)
		{
			color = sprite->img_ptr[sprite->size_line / 4 * col + line];
			if (color && color != COLOR_TRANSPARENT)
				put_pixel_image(&wolf->mlx, make_pixel(line + offset.x,
					col + offset.y), color);
		}
	}
}

void	draw_cat_legs_sprite(t_wolf *wolf, t_img *sprite)
{
	static int i = 0;

	if (i <= 20)
		put_cat_legs_in_img(wolf, sprite);
	else
	{
		wolf->player.is_attacking = FALSE;
		i = 0;
		return ;
	}
	i++;
}
