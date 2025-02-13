/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:44:27 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 18:06:58 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_object	*init_sorted_objects_list(void)
{
	t_object *sorted;

	if (!(sorted = (t_object*)malloc(sizeof(t_object))))
		exit_on_error(MALLOC_ERROR);
	ft_bzero(sorted, sizeof(t_object));
	sorted->distance = INFINITY;
	sorted->next = NULL;
	return (sorted);
}

size_t		count_objects(t_object *objects)
{
	t_object	*cur_obj;
	size_t		n;

	n = 0;
	cur_obj = objects;
	while (cur_obj)
	{
		cur_obj = cur_obj->next;
		n++;
	}
	return (n);
}

void		sort_objects(t_object **objects, t_wolf *wolf)
{
	t_object *cur_obj;
	t_object *sorted;
	t_object *cur_sorted;
	t_object *prev_sorted;
	t_object *next_obj;

	compute_object_distances(*objects, wolf);
	cur_obj = *objects;
	sorted = init_sorted_objects_list();
	while (cur_obj)
	{
		next_obj = cur_obj->next;
		cur_sorted = sorted;
		while (cur_sorted && (cur_obj->distance < cur_sorted->distance))
		{
			prev_sorted = cur_sorted;
			cur_sorted = cur_sorted->next;
		}
		prev_sorted->next = cur_obj;
		cur_obj->next = cur_sorted;
		cur_obj = next_obj;
	}
	*objects = sorted->next;
	free(sorted);
}
