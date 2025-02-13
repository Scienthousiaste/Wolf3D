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
	t_img img;

	ft_bzero(&img, sizeof(t_img));
	if (!(img.image = mlx_xpm_file_to_image(wolf->mlx.connect,
			file, &img.width, &img.height)))
		parsing_error(IMAGE_ERROR, 0);
	if (!(img.img_ptr = (int*)mlx_get_data_addr(img.image,
			&img.bits_per_pixel, &img.size_line, &img.endian)))
		parsing_error(IMAGE_ERROR, 0);
	return (img);
}
