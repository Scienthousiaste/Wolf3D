/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:48:27 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 17:42:28 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	parse_char(t_wolf *wolf, t_pixel coord, char *line, int *ret_line)
{
	if (line[coord.x] == PLAYER_CHAR)
	{
		if (!isnan(wolf->player.position.x))
			parsing_error(TWO_STARTING_POSITION, coord.y);
		wolf->player.position.x = (double)(coord.x) + 0.501;
		wolf->player.position.y = (double)(coord.y) + 0.501;
		ret_line[coord.x] = EMPTY_CHAR;
	}
	else if (ft_strchr(SPRITE_CHARS, line[coord.x]))
	{
		add_object(wolf, line[coord.x], make_point(coord.x + 0.5,
			coord.y + 0.5));
		ret_line[coord.x] = EMPTY_CHAR;
	}
	else
		ret_line[coord.x] = (int)line[coord.x];
}

int		*parse_line(char *line, t_wolf *wolf, size_t line_number)
{
	int		i;
	int		*ret_line;
	t_map	*map;

	map = &wolf->map;
	i = -1;
	if (!map->width)
	{
		if (line_number > 0)
			parsing_error(INVALID_LINE_LENGTH, line_number);
		map->width = ft_strlen(line);
	}
	else if (ft_strlen(line) != map->width)
		parsing_error(INVALID_LINE_LENGTH, line_number);
	if (!(ret_line = (int*)malloc(sizeof(int) * map->width)))
		parsing_error(MALLOC_ERROR, line_number);
	while (++i < (int)ft_strlen(line))
		parse_char(wolf, make_pixel(i, line_number), line, ret_line);
	check_correct_borders(line, &wolf->map, line_number);
	return (ret_line);
}

size_t	count_lines(char *filename)
{
	int		fd;
	int		number_lines;
	int		ret;
	char	*current_line;

	if ((fd = open(filename, O_RDONLY)) < 0)
		parsing_error(FILE_READING_ERROR, 0);
	number_lines = 0;
	while ((ret = get_next_line(fd, &current_line)))
	{
		number_lines++;
		if (ret == -1)
			parsing_error(GNL_ERROR, number_lines);
		check_only_correct_chars(current_line, number_lines);
		ft_strdel(&current_line);
	}
	close(fd);
	return (number_lines);
}

int		parse_map(char *filename, t_wolf *wolf)
{
	int		ret;
	int		fd;
	char	*current_line;
	size_t	i;

	if ((fd = open(filename, O_RDONLY)) < 0)
		parsing_error(FILE_READING_ERROR, 0);
	init_map(wolf, count_lines(filename));
	i = 0;
	while ((ret = get_next_line(fd, &current_line)))
	{
		if (ret == -1)
			parsing_error(GNL_ERROR, wolf->map.height);
		wolf->map.array[i] = parse_line(current_line, wolf, i);
		ft_strdel(&current_line);
		i++;
	}
	if (isnan(wolf->player.position.x))
		parsing_error(NO_STARTING_POSITION, 0);
	if (count_objects(wolf->map.objects) > NB_MAX_OBJECTS)
		parsing_error(TOO_MUCH_OBJECTS, 0);
	sort_objects(&wolf->map.objects, wolf);
	close(fd);
	return (1);
}
