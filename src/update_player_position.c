/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:25:52 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 11:36:28 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	update_player_direction(t_wolf *wolf, double angle_delta)
{
	t_player *player;

	player = &wolf->player;
	player->angle = fmod(player->angle + angle_delta, 2 * M_PI);
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	player->direction.x = cos(player->angle);
	player->direction.y = sin(player->angle);
}

void	remove_object(t_object **objs, t_object *obj)
{
	t_object *cur;
	t_object *prev;

	prev = NULL;
	cur = *objs;
	while (cur != NULL)
		if (cur == obj)
		{
			if (prev)
				prev->next = cur->next;
			else
			{
				if (cur->next)
					*objs = cur->next;
				else
					*objs = NULL;
			}
			free(cur);
			return ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
}

void	pick_up_objects(t_wolf *wolf)
{
	t_object *object;

	object = wolf->map.objects;
	while (object != NULL)
	{
		if (distance(wolf->player.position, object->position)
				< DISTANCE_PICK_UP)
		{
			if (object->type == MUSHROOM)
			{
				start_mushroom_effects(wolf);
				remove_object(&wolf->map.objects, object);
				return ;
			}
			else if (object->type == CATNIP)
			{
				start_catnip_effects(wolf);
				remove_object(&wolf->map.objects, object);
				return ;
			}
			else if (object->type == CHAIR)
				object->sprite = &wolf->sprites[CHAIRHAIR_SPRITE];
		}
		object = object->next;
	}
}

void	update_player_position(t_wolf *wolf, t_point direction, double move)
{
	t_player	*player;
	t_map		*map;
	double		next_x;
	double		next_y;

	player = &wolf->player;
	map = &wolf->map;
	next_x = player->position.x + move * direction.x;
	next_y = player->position.y + move * direction.y;
	if ((int)next_x < (int)map->width && (int)next_x >= 0
			&& map->array[(int)player->position.y][(int)(next_x)] == EMPTY_CHAR)
	{
		player->position.x = next_x;
	}
	if ((int)next_y < (int)map->height && (int)next_y >= 0 &&
			map->array[(int)(next_y)][(int)player->position.x] == EMPTY_CHAR)
	{
		player->position.y = next_y;
	}
	pick_up_objects(wolf);
}

void	update_player(t_wolf *wolf)
{
	t_player	*player;

	player = &wolf->player;
	if (player->is_moving == 1)
		update_player_position(wolf, player->direction,
			player->velocity * player->running_multiple);
	else if (player->is_moving == -1)
		update_player_position(wolf, player->direction,
			-player->velocity * player->running_multiple);
	if (player->is_pivoting == 1 && !player->is_strafing)
		update_player_direction(wolf, DELTA_ANGLE);
	else if (player->is_pivoting == -1 && !player->is_strafing)
		update_player_direction(wolf, -DELTA_ANGLE);
	else if (player->is_strafing && player->is_pivoting != 0)
	{
		update_player_position(wolf,
			make_point(
				cos(player->angle + M_PI / 2),
				sin(player->angle + M_PI / 2)),
			player->is_pivoting * player->velocity);
	}
}
