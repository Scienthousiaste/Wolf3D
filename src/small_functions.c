/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 12:25:32 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/05 18:07:47 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double		degrees_to_radians(double degrees)
{
	return ((degrees * M_PI) / 180.0);
}

int			radians_to_degrees(double radians)
{
	return (round(radians * (180.0 / M_PI)));
}

t_pixel		position_to_minimap_pixel(t_wolf *wolf, t_point pos)
{
	t_pixel p;

	p.x = round(wolf->map.offset_x + pos.x * wolf->map.square_side);
	p.y = round(wolf->map.offset_y + pos.y * wolf->map.square_side);
	return (p);
}

t_couple	couple(int a, int b)
{
	t_couple couple;

	couple.a = a;
	couple.b = b;
	return (couple);
}

t_pixel		make_pixel(int x, int y)
{
	t_pixel p;

	p.x = x;
	p.y = y;
	return (p);
}
