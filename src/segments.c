/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 17:10:02 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 12:47:56 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	new_wall_to_non_wall(t_map *map, t_pixel p, int start_segment,
		t_bool horizontal)
{
	if (horizontal)
	{
		return (is_wall(map, p.y, p.x)
				&& !is_wall(map, p.y + 1, p.x)
				&& start_segment == -1);
	}
	return (is_wall(map, p.y, p.x)
			&& !is_wall(map, p.y, p.x + 1)
			&& start_segment == -1);
}

int	was_wall_to_non_wall(t_map *map, t_pixel p, int start_segment,
		t_bool horizontal)
{
	if (horizontal)
	{
		return (is_wall(map, p.y, p.x)
				&& is_wall(map, p.y + 1, p.x)
				&& start_segment != -1);
	}
	return (is_wall(map, p.y, p.x)
			&& is_wall(map, p.y, p.x + 1)
			&& start_segment != -1);
}

int	new_non_wall_to_wall(t_map *map, t_pixel p, int start_segment,
		t_bool horizontal)
{
	if (horizontal)
	{
		return (!is_wall(map, p.y, p.x)
				&& is_wall(map, p.y + 1, p.x)
				&& start_segment == -1);
	}
	return (!is_wall(map, p.y, p.x)
			&& is_wall(map, p.y, p.x + 1)
			&& start_segment == -1);
}

int	was_non_wall_to_wall(t_map *map, t_pixel p, int start_segment,
		t_bool horizontal)
{
	if (horizontal)
	{
		return (!is_wall(map, p.y, p.x)
				&& !is_wall(map, p.y + 1, p.x)
				&& start_segment != -1);
	}
	return (!is_wall(map, p.y, p.x)
			&& !is_wall(map, p.y, p.x + 1)
			&& start_segment != -1);
}

int	is_wall(t_map *map, int i, int j)
{
	if (ft_strchr(WALL_CHARS, map->array[i][j]))
	{
		return (TRUE);
	}
	return (FALSE);
}
