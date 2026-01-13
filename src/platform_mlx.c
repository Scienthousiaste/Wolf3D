/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Platform implementation using MLX42 (desktop)                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLATFORM_WEB
# include "platform.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>

struct s_platform
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	int					width;
	int					height;
	int					should_close;
	t_frame_callback	frame_cb;
	void				*frame_param;
	t_key_callback		key_cb;
	void				*key_param;
	int					keys[PKEY_COUNT];
};

static t_platform_key	mlx_key_to_platform(keys_t key)
{
	if (key == MLX_KEY_ESCAPE)
		return (PKEY_ESCAPE);
	if (key == MLX_KEY_UP)
		return (PKEY_UP);
	if (key == MLX_KEY_DOWN)
		return (PKEY_DOWN);
	if (key == MLX_KEY_LEFT)
		return (PKEY_LEFT);
	if (key == MLX_KEY_RIGHT)
		return (PKEY_RIGHT);
	if (key == MLX_KEY_LEFT_SHIFT || key == MLX_KEY_RIGHT_SHIFT)
		return (PKEY_SHIFT);
	if (key == MLX_KEY_LEFT_ALT || key == MLX_KEY_RIGHT_ALT)
		return (PKEY_ALT);
	if (key == MLX_KEY_SPACE)
		return (PKEY_SPACE);
	if (key == MLX_KEY_1)
		return (PKEY_1);
	if (key == MLX_KEY_2)
		return (PKEY_2);
	if (key == MLX_KEY_M)
		return (PKEY_M);
	return (PKEY_NONE);
}

static void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_platform		*p;
	t_platform_key	pkey;
	int				pressed;

	p = (t_platform *)param;
	pkey = mlx_key_to_platform(keydata.key);
	if (pkey == PKEY_NONE)
		return ;
	pressed = (keydata.action == MLX_PRESS);
	if (keydata.action == MLX_RELEASE)
		pressed = 0;
	else if (keydata.action == MLX_PRESS)
		pressed = 1;
	else
		return ;
	p->keys[pkey] = pressed;
	if (p->key_cb)
		p->key_cb(pkey, pressed, p->key_param);
}

static void	frame_handler(void *param)
{
	t_platform	*p;

	p = (t_platform *)param;
	if (p->frame_cb)
		p->frame_cb(p->frame_param);
}

static void	close_handler(void *param)
{
	t_platform	*p;

	p = (t_platform *)param;
	p->should_close = 1;
}

t_platform	*platform_init(int width, int height, const char *title)
{
	t_platform	*p;

	p = (t_platform *)malloc(sizeof(t_platform));
	if (!p)
		return (NULL);
	memset(p, 0, sizeof(t_platform));
	p->width = width;
	p->height = height;
	p->mlx = mlx_init(width, height, title, false);
	if (!p->mlx)
	{
		free(p);
		return (NULL);
	}
	p->image = mlx_new_image(p->mlx, width, height);
	if (!p->image)
	{
		mlx_terminate(p->mlx);
		free(p);
		return (NULL);
	}
	mlx_image_to_window(p->mlx, p->image, 0, 0);
	mlx_key_hook(p->mlx, &key_handler, p);
	mlx_close_hook(p->mlx, &close_handler, p);
	return (p);
}

void	platform_destroy(t_platform *p)
{
	if (!p)
		return ;
	if (p->image)
		mlx_delete_image(p->mlx, p->image);
	if (p->mlx)
		mlx_terminate(p->mlx);
	free(p);
}

uint8_t	*platform_get_framebuffer(t_platform *p)
{
	if (!p || !p->image)
		return (NULL);
	return (p->image->pixels);
}

void	platform_present(t_platform *p)
{
	(void)p;
}

void	platform_set_frame_callback(t_platform *p,
		t_frame_callback cb, void *param)
{
	if (!p)
		return ;
	p->frame_cb = cb;
	p->frame_param = param;
	mlx_loop_hook(p->mlx, &frame_handler, p);
}

void	platform_set_key_callback(t_platform *p,
		t_key_callback cb, void *param)
{
	if (!p)
		return ;
	p->key_cb = cb;
	p->key_param = param;
}

void	platform_run(t_platform *p)
{
	if (!p)
		return ;
	mlx_loop(p->mlx);
}

int	platform_should_close(t_platform *p)
{
	if (!p)
		return (1);
	return (p->should_close);
}

void	platform_request_close(t_platform *p)
{
	if (!p)
		return ;
	p->should_close = 1;
	mlx_close_window(p->mlx);
}

int	platform_is_key_down(t_platform *p, t_platform_key key)
{
	if (!p || key <= PKEY_NONE || key >= PKEY_COUNT)
		return (0);
	return (p->keys[key]);
}

uint8_t	*platform_load_png(const char *path, int *width, int *height)
{
	mlx_texture_t	*tex;
	uint8_t			*data;
	size_t			size;

	tex = mlx_load_png(path);
	if (!tex)
		return (NULL);
	*width = tex->width;
	*height = tex->height;
	size = tex->width * tex->height * 4;
	data = (uint8_t *)malloc(size);
	if (data)
		memcpy(data, tex->pixels, size);
	mlx_delete_texture(tex);
	return (data);
}

void	platform_free_texture(uint8_t *data)
{
	free(data);
}

static void	*sound_thread(void *arg)
{
	char	cmd[512];
	char	*path;

	path = (char *)arg;
	snprintf(cmd, sizeof(cmd), "afplay \"%s\"", path);
	system(cmd);
	free(path);
	return (NULL);
}

void	platform_play_sound(const char *path)
{
	pthread_t	tid;
	char		*path_copy;

	path_copy = strdup(path);
	if (!path_copy)
		return ;
	if (pthread_create(&tid, NULL, sound_thread, path_copy) == 0)
		pthread_detach(tid);
	else
		free(path_copy);
}

#endif
