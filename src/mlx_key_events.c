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

void	enable_key_events(t_wolf *wolf)
{
	t_mlx *mlx;

	mlx = &wolf->mlx;
	mlx_hook(mlx->window, KEY_PRESS, 0, &key_press_handler, wolf);
	mlx_hook(mlx->window, KEY_RELEASE, 0, &key_release_handler, wolf);
}

int		key_press_handler(int keycode, t_wolf *wolf)
{
	if (keycode == ESCAPE_KEY)
		close_program(&wolf->mlx);
	else if (keycode == ARROW_UP)
		wolf->player.is_moving = 1;
	else if (keycode == ARROW_DOWN)
		wolf->player.is_moving = -1;
	else if (keycode == ARROW_LEFT)
		wolf->player.is_pivoting = -1;
	else if (keycode == ARROW_RIGHT)
		wolf->player.is_pivoting = 1;
	else if (keycode == SHIFT_LEFT || keycode == SHIFT_RIGHT)
		wolf->player.running_multiple = 2;
	else if (keycode == ALT_LEFT || keycode == ALT_RIGHT)
		wolf->player.is_strafing = 1;
	key_press_handle_attack(keycode, wolf);
	key_press_handle_minimap(keycode, wolf);
	return (0);
}

int		key_release_handler(int keycode, t_wolf *wolf)
{
	if (keycode == ARROW_UP)
		wolf->player.is_moving = 0;
	else if (keycode == ARROW_DOWN)
		wolf->player.is_moving = 0;
	else if (keycode == ARROW_LEFT)
		wolf->player.is_pivoting = (wolf->player.is_pivoting == -1) ? 0 : 1;
	else if (keycode == ARROW_RIGHT)
		wolf->player.is_pivoting = (wolf->player.is_pivoting == 1) ? 0 : -1;
	else if (keycode == SHIFT_LEFT || keycode == SHIFT_RIGHT)
		wolf->player.running_multiple = 1;
	else if (keycode == ALT_LEFT || keycode == ALT_RIGHT)
		wolf->player.is_strafing = 0;
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
