/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:29:15 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 18:05:22 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		check_if_map_is_too_big(t_wolf *wolf)
{
	t_map *map;
	t_mlx *mlx;

	map = &wolf->map;
	mlx = &wolf->mlx;
	while (map->square_side > 1 &&
		(map->square_side * map->width >= (size_t)mlx->window_width ||
		map->square_side * map->height >= (size_t)mlx->window_height))
	{
		map->square_side--;
	}
	if ((map->square_side == 1 || map->square_side >= 1) &&
		(map->square_side * map->width >= (size_t)mlx->window_width ||
		map->square_side * map->height >= (size_t)mlx->window_height))
	{
		wolf->player.display_minimap = FALSE;
		ft_putendl("The map is too big to display a minimap.");
		return (1);
	}
	return (0);
}

void	check_correct_borders(char *line, t_map *map, size_t line_number)
{
	size_t i;

	i = 0;
	if (line_number == 0 || line_number == map->height - 1)
	{
		while (i < map->width)
		{
			if (!ft_strchr(WALL_CHARS, line[i]))
				parsing_error(INCORRECT_BORDER, line_number);
			i++;
		}
	}
	else
	{
		if (!ft_strchr(WALL_CHARS, line[0])
				|| !ft_strchr(WALL_CHARS, line[map->width - 1]))
			parsing_error(INCORRECT_BORDER, line_number);
	}
}

void	check_only_correct_chars(char *line, int line_number)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (!ft_strchr(MAP_CHARS, line[i]))
			parsing_error(INVALID_CHAR, line_number);
		i++;
	}
}
