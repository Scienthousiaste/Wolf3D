/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:11:18 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 15:22:10 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img	*get_sprite(char type, t_wolf *wolf)
{
	if (type == MUSHROOM)
		return (&wolf->sprites[MUSHROOM_SPRITE]);
	if (type == BARREL)
		return (&wolf->sprites[BARREL_SPRITE]);
	if (type == CAT_ARMS_ATTACK)
		return (&wolf->sprites[CAT_ARMS_SPRITE]);
	if (type == CAT_LEGS_ATTACK)
		return (&wolf->sprites[CAT_LEGS_SPRITE]);
	if (type == CATNIP)
		return (&wolf->sprites[CATNIP_SPRITE]);
	if (type == CHAIR)
		return (&wolf->sprites[CHAIR_SPRITE]);
	return (NULL);
}

t_pixel	compute_offset_sprite(t_wolf *wolf, t_object *obj,
		double dist_to_object, int height_on_screen)
{
	double	angle_to_object;
	double	delta_angle;
	t_pixel offset;

	angle_to_object = angle_between(wolf->player.position, obj->position);
	delta_angle = fmod(angle_to_object - wolf->player.angle, 2 * M_PI);
	delta_angle = delta_angle < 0 ? delta_angle + 2 * M_PI : delta_angle;
	offset.x = ((int)(wolf->mlx.window_width * delta_angle
				/ wolf->player.field_of_view + (wolf->mlx.window_width / 2)))
				% wolf->mlx.window_width;
	offset.y = wolf->mlx.window_height / 2
		+ wolf->mlx.window_height / dist_to_object - height_on_screen;
	return (offset);
}

void	draw_sprite_pixel(t_draw_data *dd, t_pixel *it, t_wolf *wolf,
		t_img *sprite)
{
	dd->color = sprite->img_ptr[
		(sprite->size_line / 4) * dd->sprite_pixel.y
			+ dd->sprite_pixel.x];
	if ((it->x + dd->offset.x) < wolf->mlx.window_width
			&& (it->x + dd->offset.x) >= 0
			&& (it->y + dd->offset.y) < wolf->mlx.window_height
			&& (it->y + dd->offset.y) >= 0
			&& dd->sprite_pixel.y < sprite->height
			&& dd->sprite_pixel.x < sprite->width
			&& dd->color
			&& dd->color != COLOR_TRANSPARENT)
	{
		put_pixel_image(&wolf->mlx, make_pixel(it->x + dd->offset.x,
					it->y + dd->offset.y), dd->color);
	}
}

void	draw_sprite(t_wolf *wolf, t_object *obj, t_img *sprite)
{
	t_draw_data	dd;
	t_pixel		it;
	double		dist_to_object;

	dist_to_object = distance(obj->position, wolf->player.position);
	dd.size_on_screen.y = (int)((double)obj->height / dist_to_object);
	dd.size_on_screen.x = (int)((double)obj->width / dist_to_object);
	dd.offset = compute_offset_sprite(wolf, obj, dist_to_object,
			dd.size_on_screen.y);
	dd.max_y = (dd.offset.y + dd.size_on_screen.y < wolf->mlx.window_height) ?
			dd.size_on_screen.y : wolf->mlx.window_height - dd.offset.y - 1;
	if (dd.size_on_screen.y >= MIN_HEIGHT_SPRITE && (it.x = -1))
		while (++it.x < dd.size_on_screen.x && (it.y = -1))
		{
			dd.prop.x = (double)it.x / (double)dd.size_on_screen.x;
			dd.sprite_pixel.x = floor(dd.prop.x * sprite->width);
			while (++it.y < dd.max_y)
				if (is_ground_pixel(wolf, make_pixel(it.x + dd.offset.x,
					dd.max_y + dd.offset.y)))
				{
					dd.prop.y = (double)it.y / (double)dd.size_on_screen.y;
					dd.sprite_pixel.y = floor(dd.prop.y * sprite->height);
					draw_sprite_pixel(&dd, &it, wolf, sprite);
				}
		}
}

void	draw_sprites(t_wolf *wolf)
{
	t_object	*cur;
	t_img		*sprite;

	cur = wolf->map.objects;
	while (cur)
	{
		if (is_in_fov(wolf, cur->position))
			draw_sprite(wolf, cur, cur->sprite);
		cur = cur->next;
	}
	if (wolf->player.is_attacking && wolf->player.weapon == ARM)
	{
		sprite = get_sprite(CAT_ARMS_ATTACK, wolf);
		draw_cat_arm_sprite(wolf, sprite);
	}
	if (wolf->player.is_attacking && wolf->player.weapon == LEGS)
	{
		sprite = get_sprite(CAT_LEGS_ATTACK, wolf);
		draw_cat_legs_sprite(wolf, sprite);
	}
}
