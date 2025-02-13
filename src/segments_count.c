/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:15:24 by tbehra            #+#    #+#             */
/*   Updated: 2019/08/06 17:23:01 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

size_t	count_vertical_segments(t_map *map, t_pixel p)
{
	size_t		count;
	t_segment	s;

	count = 0;
	while (++p.x < (int)map->width - 1 && reinit_segment(&s) && (p.y = -1))
		while (++p.y < (int)map->height)
		{
			if (new_wall_to_non_wall(map, p, s.start.y, 0)
			|| (new_non_wall_to_wall(map, p, s.start.y, 0)))
				set_segment(&s, new_wall_to_non_wall(map, p, s.start.y, 0) ?
				map->array[p.y][p.x] : map->array[p.y][p.x + 1],
				-1, make_point(-1, p.y));
			else if ((w_to_nw_texture_change(map, p, s, 0))
			|| (nw_to_w_texture_change(map, p, s, 0)))
				count += 1 + set_segment(&s,
					nw_to_w_texture_change(map, p, s, 0) ?
					map->array[p.y][p.x + 1]
					: map->array[p.y][p.x], -1, make_point(-1, p.y));
			else if ((was_wall_to_non_wall(map, p, s.start.y, 0))
				|| (was_non_wall_to_wall(map, p, s.start.y, 0)))
				count += reinit_segment(&s);
		}
	return (count);
}

size_t	count_horizontal_segments(t_map *map, t_pixel p)
{
	size_t		count;
	t_segment	s;

	count = 0;
	while (++p.y < (int)map->height - 1 && reinit_segment(&s) && (p.x = -1))
		while (++p.x < (int)map->width)
		{
			if (new_wall_to_non_wall(map, p, s.start.x, 1)
			|| (new_non_wall_to_wall(map, p, s.start.x, 1)))
				set_segment(&s, new_wall_to_non_wall(map, p, s.start.x, 1) ?
				map->array[p.y][p.x] : map->array[p.y + 1][p.x],
				-1, make_point(p.x, -1));
			else if ((w_to_nw_texture_change(map, p, s, 1))
			|| (nw_to_w_texture_change(map, p, s, 1)))
				count += 1 + set_segment(&s,
					nw_to_w_texture_change(map, p, s, 1) ?
					map->array[p.y + 1][p.x] : map->array[p.y][p.x], -1,
					make_point(p.x, -1));
			else if ((was_wall_to_non_wall(map, p, s.start.x, 1))
				|| (was_non_wall_to_wall(map, p, s.start.x, 1)))
				count += reinit_segment(&s);
		}
	return (count);
}
