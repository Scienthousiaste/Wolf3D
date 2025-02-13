/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 10:25:15 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 12:48:30 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			get_points(t_wolf *wolf)
{
	t_points_list	*unique_points;
	t_points_list	*cur;
	size_t			i;

	i = 0;
	unique_points = NULL;
	while (i < wolf->map.segments_length)
	{
		if (is_not_in(wolf->map.segments[i].start, unique_points,
				wolf->map.segments[i]))
		{
			unique_points = add_to_list(&unique_points,
				wolf->map.segments[i].start, &wolf->map.segments[i]);
		}
		if (is_not_in(wolf->map.segments[i].end, unique_points,
				wolf->map.segments[i]))
		{
			unique_points = add_to_list(&unique_points,
				wolf->map.segments[i].end, &wolf->map.segments[i]);
		}
		i++;
	}
	wolf->map.unique_points = unique_points;
	cur = wolf->map.unique_points;
}

int				is_not_in(t_point p, t_points_list *unique_points,
		t_segment segment)
{
	t_points_list *cur;

	if (!unique_points)
		return (1);
	cur = unique_points;
	while (cur)
	{
		if (is_same_point(cur->p, p) && is_same_segment(*cur->segment, segment))
			return (0);
		cur = cur->next;
	}
	return (1);
}

t_bool			is_same_point(t_point p1, t_point p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

t_point			make_point(double x, double y)
{
	t_point p;

	p.x = x;
	p.y = y;
	return (p);
}

t_points_list	*add_to_list(t_points_list **points_list,
		t_point point, t_segment *segment)
{
	t_points_list *new;
	t_points_list *cur;
	t_points_list *prev;

	if (!(new = (t_points_list*)malloc(sizeof(t_points_list))))
		exit_on_error(MALLOC_ERROR);
	new->p = point;
	new->next = NULL;
	new->segment = segment;
	new->angle = NAN;
	if (!(*points_list))
		return (new);
	else
	{
		prev = NULL;
		cur = *points_list;
		while (cur)
		{
			prev = cur;
			cur = cur->next;
		}
		if (prev)
			prev->next = new;
	}
	return (*points_list);
}
