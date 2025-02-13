/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:24:01 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/04 15:48:57 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	vertical_line(t_wolf *wolf, t_pixel start, int y_end, int color)
{
	int		end;
	t_pixel	p;

	p.x = start.x;
	p.y = (start.y <= y_end) ? start.y : y_end;
	end = (start.y <= y_end) ? y_end : start.y;
	while (p.y < end)
	{
		put_pixel_image(&wolf->mlx, p, color);
		p.y++;
	}
	return (1);
}

int	line_x_inc(t_wolf *wolf, t_pixel start, t_pixel end, int color)
{
	int		dx;
	int		dy;
	int		diff;
	int		yi;
	t_pixel	p;

	dx = end.x - start.x;
	dy = end.y - start.y;
	yi = (dy < 0) ? -1 : 1;
	dy = (dy < 0) ? -dy : dy;
	diff = 2 * dy - dx;
	p.x = start.x;
	p.y = start.y;
	while (p.x <= end.x)
	{
		put_pixel_image(&wolf->mlx, p, color);
		if (diff > 0)
		{
			p.y += yi;
			diff -= 2 * dx;
		}
		diff += 2 * dy;
		p.x++;
	}
	return (1);
}

int	line_y_inc(t_wolf *wolf, t_pixel start, t_pixel end, int color)
{
	int		dx;
	int		dy;
	int		diff;
	int		xi;
	t_pixel p;

	dx = end.x - start.x;
	dy = end.y - start.y;
	xi = (dx < 0) ? -1 : 1;
	dx = (dx < 0) ? -dx : dx;
	diff = 2 * dy - dx;
	p.x = start.x;
	p.y = start.y;
	while (p.y <= end.y)
	{
		put_pixel_image(&wolf->mlx, p, color);
		if (diff > 0)
		{
			p.x += xi;
			diff -= 2 * dy;
		}
		diff += 2 * dx;
		p.y++;
	}
	return (1);
}

int	trace_line(t_wolf *wolf, t_pixel start, t_pixel end, int color)
{
	int	dx;
	int dy;

	dx = end.x - start.x;
	if (dx == 0)
		return (vertical_line(wolf, start, end.y, color));
	dy = end.y - start.y;
	if ((dy / dx) >= 1)
	{
		if (dy < 0)
			return (line_y_inc(wolf, end, start, color));
		else
			return (line_y_inc(wolf, start, end, color));
	}
	else if ((dy / dx) <= -1)
	{
		if (dx < 0)
			return (line_y_inc(wolf, start, end, color));
		else
			return (line_y_inc(wolf, end, start, color));
	}
	else if (dx < 0)
		return (line_x_inc(wolf, end, start, color));
	return (line_x_inc(wolf, start, end, color));
}
