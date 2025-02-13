/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_visible_segments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:31:16 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 16:28:55 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			add_border_fov_intersections(t_wolf *wolf)
{
	t_points_list	closest;
	t_half_line		ray;
	t_bool			found;

	ray = make_half_line(wolf->player.position, make_point(
			cos(wolf->player.angle + wolf->player.field_of_view / 2),
			sin(wolf->player.angle + wolf->player.field_of_view / 2)));
	found = FALSE;
	closest = find_closest_segment_intersection(wolf, ray, &found);
	if (found == TRUE)
		wolf->first_intersection = insert_intersection(wolf, closest.p,
				closest.segment, closest.angle);
	found = FALSE;
	ray = make_half_line(wolf->player.position, make_point(
			cos(wolf->player.angle - wolf->player.field_of_view / 2),
			sin(wolf->player.angle - wolf->player.field_of_view / 2)));
	closest = find_closest_segment_intersection(wolf, ray, &found);
	if (found == TRUE)
		wolf->last_intersection = insert_intersection(wolf, closest.p,
				closest.segment, closest.angle);
}

void			free_visible_segments(t_wall_list **visible_segments)
{
	t_wall_list *prev;
	t_wall_list *visible_segment;

	prev = NULL;
	visible_segment = *visible_segments;
	while (visible_segment)
	{
		prev = visible_segment;
		visible_segment = visible_segment->next;
		free(prev);
	}
	*visible_segments = NULL;
}

t_points_list	get_closest_points_list(t_wolf *wolf, t_bool *found,
		t_points_list *extremity, int i)
{
	double			angle;
	t_half_line		ray;

	angle = angle_between(wolf->player.position, extremity->p)
			+ (i - 1) * EPSILON_ANGLE;
	ray = make_half_line(wolf->player.position, make_point(
			cos(angle), sin(angle)));
	*found = FALSE;
	return (find_closest_segment_intersection(wolf, ray, found));
}

void			get_visible_segments(t_wolf *wolf, t_points_list *extremity)
{
	t_points_list	closest;
	int				i;
	t_bool			found;

	free_visible_segments(&wolf->visible_segments);
	free_points_list(&wolf->intersections);
	while (extremity)
	{
		if (is_in_fov_angle(wolf, extremity->p))
		{
			i = 0;
			while (i < 3)
			{
				closest = get_closest_points_list(wolf, &found, extremity, i);
				if (found == TRUE)
					insert_intersection(wolf, closest.p, closest.segment,
						closest.angle);
				i++;
			}
		}
		extremity = extremity->next;
	}
	add_border_fov_intersections(wolf);
	make_visible_segments(wolf);
}

void			make_visible_segments(t_wolf *wolf)
{
	t_points_list	*intersection;
	t_wall_list		*new;
	t_wall_list		*prev;

	intersection = wolf->intersections;
	prev = NULL;
	while (intersection)
	{
		if (is_not_in_segments(wolf->visible_segments, intersection->segment))
		{
			if (!(new = (t_wall_list*)malloc(sizeof(t_wall_list))))
				exit_on_error(MALLOC_ERROR);
			copy_segment_in(intersection->segment, &new->wall);
			new->distance = distance(intersection->p, wolf->player.position);
			new->next = NULL;
			if (!wolf->visible_segments)
				wolf->visible_segments = new;
			if (prev)
				prev->next = new;
			prev = new;
		}
		intersection = intersection->next;
	}
}
