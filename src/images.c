/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:35:52 by tbehra            #+#    #+#             */
/*   Updated: 2019/08/25 14:32:35 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img	make_img(t_wolf *wolf, char *file)
{
	t_img	img;
	int		width;
	int		height;

	(void)wolf;
	ft_bzero(&img, sizeof(t_img));
	img.img_ptr = platform_load_png(file, &width, &height);
	if (!img.img_ptr)
	{
		ft_putstr_fd("Warning: Could not load texture: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		img.width = 64;
		img.height = 64;
		img.img_ptr = (uint8_t *)malloc(64 * 64 * 4);
		if (!img.img_ptr)
			parsing_error(IMAGE_ERROR, 0);
		ft_bzero(img.img_ptr, 64 * 64 * 4);
		return (img);
	}
	img.width = width;
	img.height = height;
	return (img);
}
