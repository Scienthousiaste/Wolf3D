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
	t_img			img;
	mlx_texture_t	*texture;

	ft_bzero(&img, sizeof(t_img));
	texture = mlx_load_png(file);
	if (!texture)
	{
		ft_putstr_fd("Warning: Could not load texture: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		img.image = mlx_new_image(wolf->mlx.mlx, 64, 64);
		if (!img.image)
			parsing_error(IMAGE_ERROR, 0);
		img.width = 64;
		img.height = 64;
		img.img_ptr = img.image->pixels;
		return (img);
	}
	img.image = mlx_texture_to_image(wolf->mlx.mlx, texture);
	if (!img.image)
		parsing_error(IMAGE_ERROR, 0);
	img.width = texture->width;
	img.height = texture->height;
	img.img_ptr = img.image->pixels;
	mlx_delete_texture(texture);
	return (img);
}
