/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:47:12 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 12:48:23 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_half_line	make_half_line(t_point origin, t_point direction)
{
	t_half_line	half_line;

	half_line.origin = origin;
	half_line.direction = direction;
	if (direction.x == 0)
	{
		half_line.slope = (direction.y > 0) ? INFINITY : -INFINITY;
		half_line.intercept = NAN;
	}
	else
	{
		half_line.slope = direction.y / direction.x;
		half_line.intercept = origin.y - half_line.slope * origin.x;
	}
	return (half_line);
}

double		perpendicular_distance(t_segment wall,
		t_point player_pos, t_point intersect, t_half_line ray)
{
	if (wall.orientation == UP || wall.orientation == DOWN)
		return (fabs((player_pos.x - intersect.x) / ray.direction.x));
	else
		return (fabs((player_pos.y - intersect.y) / ray.direction.y));
}

double		distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

t_bool		is_on_side_of_half_line(t_point p, t_half_line line)
{
	return (((line.origin.x - p.x) / line.direction.x < 0)
			&& ((line.origin.y - p.y) / line.direction.y < 0));
}

t_bool		is_point_on_half_line(t_point p, t_half_line line)
{
	return (is_same_point(p, line.origin)
	|| (line.slope == INFINITY && p.x == line.origin.x && p.y > line.origin.y)
	|| (line.slope == -INFINITY && p.x == line.origin.x && p.y < line.origin.y)
	|| (
		((p.y + EPSILON_PRECISION) > (line.slope * p.x + line.intercept))
		&& ((p.y - EPSILON_PRECISION) < (line.slope * p.x + line.intercept))
		&& is_on_side_of_half_line(p, line)))
	? TRUE : FALSE;
}
