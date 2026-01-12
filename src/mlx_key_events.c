/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:14:30 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/13 15:28:16 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	handle_key_press(t_platform_key key, t_wolf *wolf)
{
	if (key == ESCAPE_KEY)
		close_program(&wolf->mlx);
	else if (key == ARROW_UP)
		wolf->player.is_moving = 1;
	else if (key == ARROW_DOWN)
		wolf->player.is_moving = -1;
	else if (key == ARROW_LEFT)
		wolf->player.is_pivoting = -1;
	else if (key == ARROW_RIGHT)
		wolf->player.is_pivoting = 1;
	else if (key == SHIFT_KEY)
		wolf->player.running_multiple = 2;
	else if (key == ALT_KEY)
		wolf->player.is_strafing = 1;
	key_press_handle_attack(key, wolf);
	key_press_handle_minimap(key, wolf);
}

static void	handle_key_release(t_platform_key key, t_wolf *wolf)
{
	if (key == ARROW_UP)
		wolf->player.is_moving = 0;
	else if (key == ARROW_DOWN)
		wolf->player.is_moving = 0;
	else if (key == ARROW_LEFT)
		wolf->player.is_pivoting = (wolf->player.is_pivoting == -1) ? 0 : 1;
	else if (key == ARROW_RIGHT)
		wolf->player.is_pivoting = (wolf->player.is_pivoting == 1) ? 0 : -1;
	else if (key == SHIFT_KEY)
		wolf->player.running_multiple = 1;
	else if (key == ALT_KEY)
		wolf->player.is_strafing = 0;
}

static void	key_handler(t_platform_key key, int pressed, void *param)
{
	t_wolf	*wolf;

	wolf = (t_wolf *)param;
	if (pressed)
		handle_key_press(key, wolf);
	else
		handle_key_release(key, wolf);
}

void	enable_key_events(t_wolf *wolf)
{
	platform_set_key_callback(wolf->mlx.platform, &key_handler, wolf);
}

int		key_press_handler(int keycode, t_wolf *wolf)
{
	(void)keycode;
	(void)wolf;
	return (0);
}

int		key_release_handler(int keycode, t_wolf *wolf)
{
	(void)keycode;
	(void)wolf;
	return (0);
}

int		key_press_handle_attack(int keycode, t_wolf *wolf)
{
	pthread_t thread;

	if (keycode == SPACEBAR && wolf->player.is_attacking == FALSE)
	{
		wolf->player.is_attacking = TRUE;
		if (pthread_create(&thread, NULL, meow_thread, NULL) == THREAD_ERROR)
			ft_putstr_fd("error: could not create a new thread\n", 2);
	}
	else if (keycode == KEY_ONE && wolf->player.is_attacking == FALSE)
		wolf->player.weapon = ARM;
	else if (keycode == KEY_TWO && wolf->player.is_attacking == FALSE)
		wolf->player.weapon = LEGS;
	return (0);
}

int		key_press_handle_minimap(int keycode, t_wolf *wolf)
{
	if (keycode == KEY_M)
	{
		wolf->player.display_minimap = (wolf->player.display_minimap == TRUE) ?
			FALSE : TRUE;
	}
	return (0);
}
