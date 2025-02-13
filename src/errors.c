/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:56:04 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/11 17:41:09 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	exit_on_error(int error)
{
	ft_putstr_fd("An error occured\n", 2);
	exit(error);
}

void	parsing_error(int error, int line_number)
{
	const char *error_messages[NB_ERRORS] = {
		"Error while trying to read the file",
		"GNL error",
		"Invalid character",
		"The line has an invalid length",
		"There are 2 starting positions",
		"There is no starting position",
		"Malloc error",
		"There is at least a border without a wall",
		"The map is too big for the minimap to be displayed correctly",
		"A sprite or a texture couldn't be loaded",
		"Too much objects (sprites) in that map"};

	if (line_number)
	{
		ft_putstr_fd("Error line ", 2);
		ft_putnbr_fd(line_number, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error >= 0 && error < NB_ERRORS)
		ft_putstr_fd(error_messages[error], 2);
	else
		ft_putstr_fd("An error occured during parsing", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	display_usage(void)
{
	ft_putendl("Usage: ./wolf3d [pathToFile]");
}
