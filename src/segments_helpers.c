/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:33:41 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 14:27:24 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			reinit_segment(t_segment *s)
{
	s->start.y = -1;
	s->start.x = -1;
	s->end.y = -1;
	s->end.x = -1;
	s->texture = -1;
	return (1);
}

int			set_segment(t_segment *s, int texture,
		int orientation, t_point start)
{
	s->texture = texture;
	if (orientation != -1)
		s->orientation = orientation;
	s->start = start;
	return (0);
}

t_segment	make_segment(t_point start, t_point end,
		int texture, t_orient orientation)
{
	t_segment s;

	s.start = start;
	s.end = end;
	s.texture = texture;
	s.orientation = orientation;
	return (s);
}

int			is_same_segment(t_segment s, t_segment ss)
{
	return (s.start.x == ss.start.x && s.start.y == ss.start.y
			&& s.end.x == ss.end.x && s.end.y == ss.end.y);
}

void		copy_segment_in(t_segment *src, t_segment *dest)
{
	dest->start = src->start;
	dest->end = src->end;
	dest->texture = src->texture;
	dest->orientation = src->orientation;
}
