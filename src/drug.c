/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drug.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:10:05 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 15:29:31 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	start_mushroom_effects(t_wolf *wolf)
{
	wolf->player.is_under_influence += 1;
	wolf->player.drug_stop = wolf->frame_counter + DRUG_DURATION;
	wolf->color_ceilling = TRIPPY_VIOLET;
	wolf->color_ground = TRIPPY_GREEN;
}

void	start_catnip_effects(t_wolf *wolf)
{
	wolf->player.is_catniped = 1;
	wolf->player.velocity = CATNIP_MOVE;
	wolf->player.drug_stop = wolf->frame_counter + DRUG_DURATION;
}

void	mushroom_change_fov(t_wolf *wolf)
{
	double change_fov;

	change_fov = (double)((rand() % 27) - 13);
	change_fov *= DELTA_FOV * wolf->player.is_under_influence;
	if ((wolf->player.field_of_view + change_fov) > MAX_FOV)
		wolf->player.field_of_view = MAX_FOV;
	else if ((wolf->player.field_of_view + change_fov < MIN_FOV))
		wolf->player.field_of_view = MIN_FOV;
	else
		wolf->player.field_of_view = wolf->player.field_of_view
			+ change_fov;
}

void	check_events(t_wolf *wolf)
{
	if (wolf->player.is_under_influence)
	{
		if (wolf->frame_counter >= wolf->player.drug_stop)
		{
			wolf->player.is_under_influence = 0;
			wolf->player.field_of_view = NORMAL_FIELD_OF_VIEW;
			wolf->color_ceilling = BLUE;
			wolf->color_ground = GREEN;
		}
		else if (wolf->frame_counter % 8 == 0)
			mushroom_change_fov(wolf);
	}
	if (wolf->player.is_catniped && wolf->frame_counter
			>= wolf->player.drug_stop)
	{
		wolf->player.is_catniped = 0;
		wolf->player.velocity = MIN_MOVE;
	}
}
