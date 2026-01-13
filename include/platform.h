/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Platform abstraction layer for MLX42 (desktop) and Emscripten (web)      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLATFORM_H
# define PLATFORM_H

# include <stdint.h>
# include <stddef.h>

/*
** Platform-agnostic key codes
*/
typedef enum e_platform_key
{
	PKEY_NONE = 0,
	PKEY_ESCAPE,
	PKEY_UP,
	PKEY_DOWN,
	PKEY_LEFT,
	PKEY_RIGHT,
	PKEY_SHIFT,
	PKEY_ALT,
	PKEY_SPACE,
	PKEY_1,
	PKEY_2,
	PKEY_M,
	PKEY_F,
	PKEY_COUNT
}	t_platform_key;

/*
** Platform context - opaque handle
*/
typedef struct s_platform	t_platform;

/*
** Callback types
*/
typedef void	(*t_frame_callback)(void *param);
typedef void	(*t_key_callback)(t_platform_key key, int pressed, void *param);

/*
** Core platform functions
*/
t_platform		*platform_init(int width, int height, const char *title);
void			platform_destroy(t_platform *p);

/*
** Framebuffer
*/
uint8_t			*platform_get_framebuffer(t_platform *p);
void			platform_present(t_platform *p);

/*
** Main loop
*/
void			platform_set_frame_callback(t_platform *p,
					t_frame_callback cb, void *param);
void			platform_set_key_callback(t_platform *p,
					t_key_callback cb, void *param);
void			platform_run(t_platform *p);
int				platform_should_close(t_platform *p);
void			platform_request_close(t_platform *p);

/*
** Input state (for polling)
*/
int				platform_is_key_down(t_platform *p, t_platform_key key);

/*
** Texture loading (returns RGBA pixel data, caller must free)
*/
uint8_t			*platform_load_png(const char *path,
					int *width, int *height);
void			platform_free_texture(uint8_t *data);

/*
** Audio
*/
void			platform_play_sound(const char *path);

#endif
