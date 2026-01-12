/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 17:12:47 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/13 15:34:07 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	get_texture_color(t_img *texture, t_segment *wall, t_point *intersect,
		double prop_y)
{
	double	prop_x;
	int		color;
	int		idx;

	if (wall->orientation == RIGHT || wall->orientation == LEFT)
		prop_x = intersect->y - (double)(floor(intersect->y));
	else
		prop_x = intersect->x - (double)(floor(intersect->x));
	idx = ((int)(prop_y * texture->height) * texture->width
		+ (int)(prop_x * texture->width)) * 4;
	color = texture->img_ptr[idx] << 24;
	color += texture->img_ptr[idx + 1] << 16;
	color += texture->img_ptr[idx + 2] << 8;
	color += texture->img_ptr[idx + 3];
	return (color);
}

int	get_color_from_orientation(t_orient orientation)
{
	if (orientation == UP)
		return (RED);
	else if (orientation == LEFT)
		return (GRAY);
	else if (orientation == DOWN)
		return (DARK_ORANGE);
	return (ORANGE);
}

int	get_color_wall_pixel(t_wolf *wolf, t_segment wall, t_point intersect,
		double prop_y)
{
	if (wall.texture >= VARIOUS_TEXTURES
			&& wall.texture <= ('0' + NB_TEXTURES - 1))
	{
		if (wall.texture == VARIOUS_TEXTURES)
		{
			return (get_texture_color(&wolf->textures[wall.orientation],
				&wall, &intersect, prop_y));
		}
		return (
			get_texture_color(&wolf->textures[
				wall.texture - VARIOUS_TEXTURES + 1],
			&wall, &intersect, prop_y));
	}
	else
		return (get_color_from_orientation(wall.orientation));
}
