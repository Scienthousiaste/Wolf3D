/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:12:10 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 12:48:51 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	nw_to_w_texture_change(t_map *map, t_pixel p,
		t_segment s, t_bool horizontal)
{
	int start_segment;
	int texture;

	texture = s.texture;
	if (horizontal)
	{
		start_segment = s.start.x;
		return (!is_wall(map, p.y, p.x)
			&& is_wall(map, p.y + 1, p.x)
			&& start_segment != -1
			&& texture != map->array[p.y + 1][p.x]);
	}
	start_segment = s.start.y;
	return (!is_wall(map, p.y, p.x)
			&& is_wall(map, p.y, p.x + 1)
			&& start_segment != -1
			&& texture != map->array[p.y][p.x + 1]);
}

int	w_to_nw_texture_change(t_map *map, t_pixel p,
		t_segment s, t_bool horizontal)
{
	int start_segment;
	int texture;

	texture = s.texture;
	if (horizontal)
	{
		start_segment = s.start.x;
		return (is_wall(map, p.y, p.x)
			&& !is_wall(map, p.y + 1, p.x)
			&& start_segment != -1
			&& texture != map->array[p.y][p.x]);
	}
	start_segment = s.start.y;
	return (is_wall(map, p.y, p.x)
			&& !is_wall(map, p.y, p.x + 1)
			&& start_segment != -1
			&& texture != map->array[p.y][p.x]);
}
