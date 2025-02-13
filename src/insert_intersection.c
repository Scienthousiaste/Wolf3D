/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:54:06 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/05 13:56:33 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_points_list	*init_new_points_list(t_point intersection, t_segment *segment,
		double angle)
{
	t_points_list	*new;

	if (!(new = (t_points_list*)malloc(sizeof(t_points_list))))
		exit_on_error(MALLOC_ERROR);
	new->p = intersection;
	new->next = NULL;
	new->segment = segment;
	new->angle = angle;
	return (new);
}

t_point			insert_intersection(t_wolf *wolf, t_point intersection,
		t_segment *segment, double angle)
{
	t_points_list	*new;
	t_points_list	*cur;
	t_points_list	*prev;

	new = init_new_points_list(intersection, segment, angle);
	if (!(wolf->intersections))
		wolf->intersections = new;
	else
	{
		prev = NULL;
		cur = wolf->intersections;
		while (cur)
		{
			if (new->angle < cur->angle)
				break ;
			prev = cur;
			cur = cur->next;
		}
		new->next = cur;
		if (prev)
			prev->next = new;
		else
			wolf->intersections = new;
	}
	return (new->p);
}
