/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:58:57 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/11 18:06:37 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_point	get_point_to_draw(t_wolf *wolf, t_half_line ray)
{
	t_point_option	intersect;
	t_point			point_to_draw;
	double			smallest_dist;
	double			dist;
	int				idx;

	smallest_dist = INFINITY;
	point_to_draw = make_point(-1, -1);
	dist = 0;
	idx = -1;
	while (++idx < (int)wolf->map.segments_length)
	{
		intersect = find_intersection(ray, wolf->map.segments[idx]);
		if (intersect.found == TRUE)
		{
			dist = distance(wolf->player.position, intersect.p);
			if (dist < smallest_dist)
			{
				smallest_dist = dist;
				point_to_draw = intersect.p;
			}
		}
	}
	return (point_to_draw);
}

void	draw_player_view_minimap(t_wolf *wolf)
{
	t_half_line	rays[2];
	t_point		point_to_draw;
	size_t		j;

	rays[0] = make_half_line(wolf->player.position, make_point(
				cos(wolf->player.angle - wolf->player.field_of_view / HALF),
				sin(wolf->player.angle - wolf->player.field_of_view / HALF)));
	rays[1] = make_half_line(wolf->player.position, make_point(
				cos(wolf->player.angle + wolf->player.field_of_view / HALF),
				sin(wolf->player.angle + wolf->player.field_of_view / HALF)));
	j = 0;
	while (j < 2)
	{
		point_to_draw = get_point_to_draw(wolf, rays[j]);
		if (point_to_draw.x != -1)
		{
			trace_line(wolf,
				position_to_minimap_pixel(wolf, wolf->player.position),
				position_to_minimap_pixel(wolf, point_to_draw),
				RED);
		}
		j++;
	}
}

void	draw_objects(t_wolf *wolf)
{
	t_object	*cur;
	t_pixel		start;
	t_point		pstart;

	cur = wolf->map.objects;
	while (cur)
	{
		start = position_to_minimap_pixel(wolf, cur->position);
		pstart.x = (double)start.x;
		pstart.y = (double)start.y;
		draw_square(&wolf->mlx, &pstart, 3, MUSHROOM_COLOR);
		cur = cur->next;
	}
}

void	draw_visibility_polygon(t_wolf *wolf)
{
	t_points_list	*intersect;
	t_point			prev;

	prev = make_point(-1.0, -1.0);
	intersect = wolf->intersections;
	while (intersect)
	{
		if (prev.x != -1.0)
		{
			if (!(is_same_point(prev, wolf->first_intersection)
					&& is_same_point(intersect->p, wolf->last_intersection)))
				trace_line(wolf, position_to_minimap_pixel(wolf, prev),
				position_to_minimap_pixel(wolf, intersect->p), POLYGON_COLOR);
		}
		prev = intersect->p;
		intersect = intersect->next;
	}
}

void	draw_minimap(t_wolf *wolf)
{
	int			j;
	int			i;
	t_point		begin;
	t_map		*map;
	t_mlx		*mlx;

	map = &wolf->map;
	mlx = &wolf->mlx;
	if (check_if_map_is_too_big(wolf))
		return ;
	i = -1;
	while (++i < (int)(map->height) && (j = -1))
		while (++j < (int)(map->width))
		{
			begin.x = map->offset_x + j * map->square_side;
			begin.y = i * map->square_side + map->offset_y;
			if (ft_strchr(WALL_CHARS, map->array[i][j]))
				draw_square(mlx, &begin, map->square_side, MINIMAP_BORDER);
			else if (map->array[i][j] == EMPTY_CHAR)
				draw_square(mlx, &begin, map->square_side, MINIMAP_GROUND);
		}
	draw_objects(wolf);
	draw_player_view_minimap(wolf);
	draw_visibility_polygon(wolf);
}
