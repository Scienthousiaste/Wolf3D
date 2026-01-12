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

static char	*change_extension_to_png(const char *xpm_path)
{
	char	*png_path;
	size_t	len;

	len = ft_strlen(xpm_path);
	if (len < 4)
		return (ft_strdup(xpm_path));
	png_path = ft_strnew(len);
	if (!png_path)
		return (NULL);
	ft_strncpy(png_path, xpm_path, len - 3);
	ft_strcat(png_path, "png");
	return (png_path);
}

t_img	make_img(t_wolf *wolf, char *file)
{
	t_img			img;
	mlx_texture_t	*texture;
	char			*png_path;

	ft_bzero(&img, sizeof(t_img));
	png_path = change_extension_to_png(file);
	if (!png_path)
		parsing_error(MALLOC_ERROR, 0);
	texture = mlx_load_png(png_path);
	free(png_path);
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
