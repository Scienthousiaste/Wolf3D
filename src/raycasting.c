/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 21:01:29 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 13:12:01 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_points_list	find_closest_segment_intersection(t_wolf *wolf, t_half_line ray,
	t_bool *found)
{
	t_points_list	closest_intersection;
	t_point_option	intersect;
	int				i;
	double			distance_min;

	distance_min = INFINITY;
	i = -1;
	ft_bzero(&closest_intersection, sizeof(t_points_list));
	while (++i < (int)wolf->map.segments_length)
	{
		intersect = find_intersection(ray, wolf->map.segments[i]);
		if (intersect.found)
		{
			*found = TRUE;
			if (distance_min > distance(intersect.p, ray.origin))
			{
				distance_min = distance(intersect.p, ray.origin);
				closest_intersection.p = intersect.p;
				closest_intersection.segment = &wolf->map.segments[i];
				closest_intersection.angle = angle_between(ray.origin,
						intersect.p);
			}
		}
	}
	return (closest_intersection);
}

t_point_option	find_intersection(t_half_line ray, t_segment wall)
{
	t_point_option intersection;

	intersection.found = FALSE;
	if (is_same_point(wall.start, wall.end))
		return (intersection);
	if (wall.start.x == wall.end.x)
	{
		intersection.p.x = wall.start.x;
		intersection.p.y = ray.slope * wall.start.x + ray.intercept;
		if (is_point_on_half_line(intersection.p, ray)
				&& wall.start.y <= intersection.p.y
				&& wall.end.y >= intersection.p.y)
			intersection.found = TRUE;
	}
	else if (wall.start.y == wall.end.y)
	{
		intersection.p.y = wall.start.y;
		intersection.p.x = (wall.start.y - ray.intercept) / ray.slope;
		if (is_point_on_half_line(intersection.p, ray)
				&& intersection.p.x >= wall.start.x
				&& intersection.p.x <= wall.end.x)
			intersection.found = TRUE;
	}
	return (intersection);
}

void			draw_floor_ceilling_wall(t_wolf *wolf, int x,
				double distance_to_wall, t_segment wall)
{
	double	fceilling;
	int		ceilling;
	int		floor;
	int		y;
	int		color_wall;

	fceilling = ((double)wolf->mlx.window_height / HALF)
		- ((double)wolf->mlx.window_height / distance_to_wall);
	ceilling = (int)fceilling;
	floor = wolf->mlx.window_height - ceilling;
	y = 0;
	color_wall = get_color_from_orientation(wall.orientation);
	while (y < wolf->mlx.window_height)
	{
		if (y < ceilling)
			put_pixel_image(&wolf->mlx, make_pixel(x, y), wolf->color_ceilling);
		else if (y < floor)
			put_pixel_image(&wolf->mlx, make_pixel(x, y), color_wall);
		else
			put_pixel_image(&wolf->mlx, make_pixel(x, y), wolf->color_ground);
		y++;
	}
}

void			draw_column(t_wolf *wolf, int x, t_segment wall,
					t_point intersect)
{
	int		ceilling;
	int		floor;
	int		y;

	ceilling = (int)((double)wolf->mlx.window_height / HALF)
		- ((double)wolf->mlx.window_height / wolf->smallest_distance_to_wall);
	floor = wolf->mlx.window_height - ceilling;
	y = -1;
	while (++y < wolf->mlx.window_height)
	{
		if (y < ceilling)
			put_pixel_image(&wolf->mlx, make_pixel(x, y), wolf->color_ceilling);
		else if (y < floor)
			put_pixel_image(&wolf->mlx, make_pixel(x, y),
				get_color_wall_pixel(wolf, wall, intersect,
				(double)(y - ceilling) / (double)(floor - ceilling)));
		else
			put_pixel_image(&wolf->mlx, make_pixel(x, y), wolf->color_ground);
	}
}
