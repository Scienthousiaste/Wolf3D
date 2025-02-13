/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:32:17 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 14:35:27 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			is_not_in_segments(t_wall_list *walls, t_segment *current_wall)
{
	t_wall_list		*cur;

	cur = walls;
	while (cur)
	{
		if (is_same_segment(*current_wall, cur->wall))
			return (0);
		cur = cur->next;
	}
	return (1);
}

t_half_line	make_ray(t_wolf *wolf, size_t x_column)
{
	double			ray_angle;

	ray_angle = (wolf->player.angle - (wolf->player.field_of_view / HALF))
		+ (double)x_column / (double)(wolf->mlx.window_width)
		* wolf->player.field_of_view;
	return (make_half_line(wolf->player.position,
			make_point(cos(ray_angle), sin(ray_angle))));
}

void		draw_player_vision(t_wolf *wolf, int x_column,
				t_point closest_intersect_point, t_wall_list *wl)
{
	t_segment		wall;
	t_point_option	intersect;
	double			distance_to_wall;

	while (++x_column < wolf->mlx.window_width)
	{
		wolf->smallest_distance_to_wall = INFINITY;
		wl = wolf->visible_segments;
		while (wl)
		{
			intersect = find_intersection(make_ray(wolf, x_column), wl->wall);
			if (intersect.found == TRUE)
			{
				distance_to_wall = distance(intersect.p, wolf->player.position);
				if (distance_to_wall < wolf->smallest_distance_to_wall)
				{
					wolf->smallest_distance_to_wall = distance_to_wall;
					wall = wl->wall;
					closest_intersect_point = intersect.p;
				}
			}
			wl = wl->next;
		}
		draw_column(wolf, x_column, wall, closest_intersect_point);
	}
}
