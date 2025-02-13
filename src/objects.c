/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 12:31:14 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/08 15:07:21 by jmurte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	compute_object_distances(t_object *objects, t_wolf *wolf)
{
	t_object *cur_obj;

	cur_obj = objects;
	while (cur_obj)
	{
		cur_obj->distance = distance(wolf->player.position, cur_obj->position);
		cur_obj = cur_obj->next;
	}
}

int		get_height(char type, t_img *sprite)
{
	if (type == MUSHROOM)
		return (MUSHROOM_HEIGHT);
	if (type == BARREL)
		return (BARREL_HEIGHT);
	if (type == CATNIP)
		return (CATNIP_HEIGHT);
	if (type == CHAIR)
		return (CHAIR_HEIGHT);
	return (sprite->height);
}

int		get_width(char type, t_img *sprite)
{
	if (type == MUSHROOM)
		return (MUSHROOM_WIDTH);
	if (type == BARREL)
		return (BARREL_WIDTH);
	if (type == CATNIP)
		return (CATNIP_WIDTH);
	if (type == CHAIR)
		return (CHAIR_WIDTH);
	return (sprite->width);
}

void	add_object(t_wolf *wolf, char type, t_point position)
{
	t_object	*new_object;
	t_object	*cur;

	if (!(new_object = malloc(sizeof(t_object))))
		parsing_error(MALLOC_ERROR, (int)(position.y + 0.5));
	new_object->type = type;
	new_object->position = position;
	new_object->next = NULL;
	new_object->sprite = get_sprite(type, wolf);
	new_object->height = get_height(type, new_object->sprite);
	new_object->width = get_width(type, new_object->sprite);
	new_object->distance = INFINITY;
	if (!wolf->map.objects)
		wolf->map.objects = new_object;
	else
	{
		cur = wolf->map.objects;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new_object;
	}
}
