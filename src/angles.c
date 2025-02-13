/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 09:49:16 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 11:10:42 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	angle_between(t_point a, t_point b)
{
	double ret;

	if (a.x - b.x == 0.0)
	{
		if (b.y < a.y)
			return (3 * M_PI / 2);
		else
			return (M_PI / 2);
	}
	ret = fmod(atan2(b.y - a.y, b.x - a.x), 2 * M_PI);
	if (ret < 0)
		return (ret + 2 * M_PI);
	else
		return (ret);
}

int		is_in_fov_angle(t_wolf *wolf, t_point position)
{
	t_player	*player;
	double		angle_to_target;
	double		min;
	double		max;

	player = &wolf->player;
	min = fmod(player->angle - (player->field_of_view / 2), 2 * M_PI);
	max = fmod(player->angle + (player->field_of_view / 2), 2 * M_PI);
	if (min < 0)
		min += 2 * M_PI;
	if (max < min)
		max += 2 * M_PI;
	angle_to_target = angle_between(player->position, position);
	return ((angle_to_target >= min && angle_to_target <= max)
			|| (angle_to_target + 2 * M_PI >= min
				&& angle_to_target + 2 * M_PI <= max));
}

int		is_in_fov(t_wolf *wolf, t_point position)
{
	t_player	*player;
	double		angle_to_target;
	double		min;
	double		max;

	player = &wolf->player;
	min = fmod(player->angle - (player->field_of_view / 2), 2 * M_PI);
	max = fmod(player->angle + (player->field_of_view / 2), 2 * M_PI);
	if (min < 0)
		min += 2 * M_PI;
	if (max < min)
		max += 2 * M_PI;
	angle_to_target = angle_between(player->position, position);
	return (no_obstacle(wolf, position, angle_to_target)
			&& ((angle_to_target >= min && angle_to_target <= max)
				|| (angle_to_target + 2 * M_PI >= min && angle_to_target
					+ 2 * M_PI <= max)));
}

int		no_obstacle(t_wolf *wolf, t_point target, double angle)
{
	t_half_line		half_line;
	t_wall_list		*cur;
	t_point_option	intersect;

	cur = wolf->visible_segments;
	while (cur)
	{
		half_line = make_half_line(wolf->player.position,
				make_point(cos(angle), sin(angle)));
		intersect = find_intersection(half_line, cur->wall);
		if (intersect.found && (distance(wolf->player.position, intersect.p)
					< distance(wolf->player.position, target)))
			return (0);
		cur = cur->next;
	}
	return (1);
}
