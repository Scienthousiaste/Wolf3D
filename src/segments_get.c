/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:15:33 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 15:59:32 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

size_t	add_h_segment(int idx, t_segment *segments, t_couple c, t_segment *s)
{
	int end_x;
	int y_line;

	end_x = c.a;
	y_line = c.b;
	segments[idx++] = make_segment(make_point(s->start.x, y_line),
						make_point(end_x, y_line),
						s->texture, s->orientation);
	return (idx);
}

size_t	add_v_segment(int idx, t_segment *segments, t_couple c, t_segment *s)
{
	int x_column;
	int end_y;

	x_column = c.a;
	end_y = c.b;
	segments[idx++] = make_segment(make_point(x_column, s->start.y),
						make_point(x_column, end_y),
						s->texture, s->orientation);
	return (idx);
}

size_t	get_horizontal_segments(t_map *map,
		t_segment *segments, size_t idx, t_pixel p)
{
	t_segment s;

	while (++p.y < (int)map->height - 1 && (p.x = -1) && reinit_segment(&s))
		while (++p.x < (int)map->width)
			if (new_wall_to_non_wall(map, p, s.start.x, TRUE)
			|| (new_non_wall_to_wall(map, p, s.start.x, TRUE)))
				set_segment(&s, new_wall_to_non_wall(map, p, s.start.x, TRUE) ?
				map->array[p.y][p.x] : map->array[p.y + 1][p.x],
				new_wall_to_non_wall(map, p, s.start.x, TRUE) ? UP : DOWN,
				make_point(p.x, -1));
			else if (w_to_nw_texture_change(map, p, s, TRUE))
				idx = add_h_segment(idx, segments, couple(p.x, p.y + 1), &s)
			+ set_segment(&s, map->array[p.y][p.x], -1, make_point(p.x, -1));
			else if (nw_to_w_texture_change(map, p, s, TRUE))
				idx = add_h_segment(idx, segments, couple(p.x, p.y + 1), &s)
		+ set_segment(&s, map->array[p.y + 1][p.x], -1, make_point(p.x, -1));
			else if ((was_wall_to_non_wall(map, p, s.start.x, TRUE))
			|| (was_non_wall_to_wall(map, p, s.start.x, TRUE)))
			{
				idx = add_h_segment(idx, segments, couple(p.x, p.y + 1), &s);
				reinit_segment(&s);
			}
	return (idx);
}

size_t	get_vertical_segments(t_map *map,
		t_segment *segments, size_t idx, t_pixel p)
{
	t_segment s;

	while (++p.x < (int)map->width - 1 && (p.y = -1) && reinit_segment(&s))
		while (++p.y < (int)map->height)
			if (new_wall_to_non_wall(map, p, s.start.y, FALSE)
			|| (new_non_wall_to_wall(map, p, s.start.y, FALSE)))
				set_segment(&s, new_wall_to_non_wall(map, p, s.start.y, FALSE) ?
				map->array[p.y][p.x] : map->array[p.y][p.x + 1],
				new_wall_to_non_wall(map, p, s.start.y, FALSE) ? LEFT : RIGHT,
				make_point(-1, p.y));
			else if (w_to_nw_texture_change(map, p, s, FALSE))
				idx = add_v_segment(idx, segments, couple(p.x + 1, p.y), &s)
			+ set_segment(&s, map->array[p.y][p.x], -1, make_point(-1, p.y));
			else if (nw_to_w_texture_change(map, p, s, FALSE))
				idx = add_v_segment(idx, segments, couple(p.x + 1, p.y), &s)
		+ set_segment(&s, map->array[p.y][p.x + 1], -1, make_point(-1, p.y));
			else if ((was_wall_to_non_wall(map, p, s.start.y, FALSE))
			|| (was_non_wall_to_wall(map, p, s.start.y, FALSE)))
			{
				idx = add_v_segment(idx, segments, couple(p.x + 1, p.y), &s);
				reinit_segment(&s);
			}
	return (idx);
}

void	get_segments(t_wolf *wolf)
{
	t_segment	*segments;
	size_t		idx;

	wolf->map.segments_length =
		count_horizontal_segments(&wolf->map, make_pixel(-1, -1))
		+ count_vertical_segments(&wolf->map, make_pixel(-1, -1));
	if (!(segments = malloc(sizeof(t_segment) * wolf->map.segments_length)))
		exit_on_error(MALLOC_ERROR);
	idx = get_horizontal_segments(&wolf->map, segments, 0, make_pixel(-1, -1));
	idx = get_vertical_segments(&wolf->map, segments, idx, make_pixel(-1, -1));
	wolf->map.segments = segments;
}
