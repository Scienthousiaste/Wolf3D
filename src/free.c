/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:08:38 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 16:17:45 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_points_list(t_points_list **points_list)
{
	t_points_list *prev;
	t_points_list *point_list_elem;

	prev = NULL;
	point_list_elem = *points_list;
	while (point_list_elem)
	{
		prev = point_list_elem;
		point_list_elem = point_list_elem->next;
		free(prev);
	}
	*points_list = NULL;
}
