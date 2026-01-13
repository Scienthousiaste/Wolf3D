/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_web.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Platform implementation using Emscripten (web/WASM)                      */
/*                                                                            */
/* ************************************************************************** */

#ifdef PLATFORM_WEB
#include "platform.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct s_platform
{
	int					width;
	int					height;
	uint8_t				*framebuffer;
	int					should_close;
	t_frame_callback	frame_cb;
	void				*frame_param;
	t_key_callback		key_cb;
	void				*key_param;
	int					keys[PKEY_COUNT];
};

static t_platform	*g_platform = NULL;

static t_platform_key	dom_key_to_platform(const char *code)
{
	if (strcmp(code, "Escape") == 0)
		return (PKEY_ESCAPE);
	if (strcmp(code, "ArrowUp") == 0)
		return (PKEY_UP);
	if (strcmp(code, "ArrowDown") == 0)
		return (PKEY_DOWN);
	if (strcmp(code, "ArrowLeft") == 0)
		return (PKEY_LEFT);
	if (strcmp(code, "ArrowRight") == 0)
		return (PKEY_RIGHT);
	if (strcmp(code, "ShiftLeft") == 0 || strcmp(code, "ShiftRight") == 0)
		return (PKEY_SHIFT);
	if (strcmp(code, "AltLeft") == 0 || strcmp(code, "AltRight") == 0)
		return (PKEY_ALT);
	if (strcmp(code, "Space") == 0)
		return (PKEY_SPACE);
	if (strcmp(code, "Digit1") == 0)
		return (PKEY_1);
	if (strcmp(code, "Digit2") == 0)
		return (PKEY_2);
	if (strcmp(code, "KeyM") == 0)
		return (PKEY_M);
	return (PKEY_NONE);
}

static EM_BOOL	key_down_callback(int event_type,
	const EmscriptenKeyboardEvent *event, void *user_data)
{
	t_platform		*p;
	t_platform_key	pkey;

	(void)event_type;
	(void)user_data;
	p = g_platform;
	if (!p)
		return (EM_FALSE);
	pkey = dom_key_to_platform(event->code);
	if (pkey == PKEY_NONE)
		return (EM_FALSE);
	p->keys[pkey] = 1;
	if (p->key_cb)
		p->key_cb(pkey, 1, p->key_param);
	return (EM_TRUE);
}

static EM_BOOL	key_up_callback(int event_type,
	const EmscriptenKeyboardEvent *event, void *user_data)
{
	t_platform		*p;
	t_platform_key	pkey;

	(void)event_type;
	(void)user_data;
	p = g_platform;
	if (!p)
		return (EM_FALSE);
	pkey = dom_key_to_platform(event->code);
	if (pkey == PKEY_NONE)
		return (EM_FALSE);
	p->keys[pkey] = 0;
	if (p->key_cb)
		p->key_cb(pkey, 0, p->key_param);
	return (EM_TRUE);
}

static void	main_loop_callback(void)
{
	t_platform	*p;

	p = g_platform;
	if (!p)
		return ;
	if (p->frame_cb)
		p->frame_cb(p->frame_param);
}

t_platform	*platform_init(int width, int height, const char *title)
{
	t_platform	*p;

	(void)title;
	p = (t_platform *)malloc(sizeof(t_platform));
	if (!p)
		return (NULL);
	memset(p, 0, sizeof(t_platform));
	p->width = width;
	p->height = height;
	p->framebuffer = (uint8_t *)malloc(width * height * 4);
	if (!p->framebuffer)
	{
		free(p);
		return (NULL);
	}
	memset(p->framebuffer, 0, width * height * 4);
	g_platform = p;
	EM_ASM({
		var canvas = document.getElementById('canvas');
		canvas.width = $0;
		canvas.height = $1;
	}, width, height);
	emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT,
		NULL, EM_TRUE, key_down_callback);
	emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT,
		NULL, EM_TRUE, key_up_callback);
	return (p);
}

void	platform_destroy(t_platform *p)
{
	if (!p)
		return ;
	if (p->framebuffer)
		free(p->framebuffer);
	g_platform = NULL;
	free(p);
}

uint8_t	*platform_get_framebuffer(t_platform *p)
{
	if (!p)
		return (NULL);
	return (p->framebuffer);
}

void	platform_present(t_platform *p)
{
	if (!p || !p->framebuffer)
		return ;
	EM_ASM({
		var canvas = document.getElementById('canvas');
		var ctx = canvas.getContext('2d');
		var width = $0;
		var height = $1;
		var ptr = $2;
		var imageData = ctx.createImageData(width, height);
		imageData.data.set(HEAPU8.subarray(ptr, ptr + width * height * 4));
		ctx.putImageData(imageData, 0, 0);
	}, p->width, p->height, p->framebuffer);
}

void	platform_set_frame_callback(t_platform *p,
		t_frame_callback cb, void *param)
{
	if (!p)
		return ;
	p->frame_cb = cb;
	p->frame_param = param;
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
	emscripten_set_main_loop(main_loop_callback, 0, 1);
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
	emscripten_cancel_main_loop();
}

int	platform_is_key_down(t_platform *p, t_platform_key key)
{
	if (!p || key <= PKEY_NONE || key >= PKEY_COUNT)
		return (0);
	return (p->keys[key]);
}

uint8_t	*platform_load_png(const char *path, int *width, int *height)
{
	int		channels;
	uint8_t	*data;

	data = stbi_load(path, width, height, &channels, 4);
	return (data);
}

void	platform_free_texture(uint8_t *data)
{
	if (data)
		stbi_image_free(data);
}

#endif
