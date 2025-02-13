/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:49 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/13 17:12:23 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_everything(t_wolf *wolf)
{
	int i;

	i = -1;
	while (++i < NB_SPRITES)
		mlx_destroy_image(wolf->mlx.connect, wolf->sprites[i].image);
	i = -1;
	while (++i < NB_TEXTURES)
		mlx_destroy_image(wolf->mlx.connect, wolf->textures[i].image);
	i = -1;
	while (++i < (int)wolf->map.height)
		free(wolf->map.array[i]);
	free_points_list(&wolf->map.unique_points);
	free_points_list(&wolf->intersections);
	free(wolf->map.segments);
	free(wolf->map.array);
}

int		main_loop(void *param)
{
	t_wolf *wolf;

	wolf = (t_wolf*)param;
	wolf->frame_counter += 1;
	check_events(wolf);
	update_player(wolf);
	get_visible_segments(wolf, wolf->map.unique_points);
	draw_player_vision(wolf, -1, make_point(-1, -1), NULL);
	sort_objects(&wolf->map.objects, wolf);
	draw_sprites(wolf);
	if (wolf->player.display_minimap)
		draw_minimap(wolf);
	mlx_put_image_to_window(wolf->mlx.connect, wolf->mlx.window,
		wolf->mlx.img_ptr, 0, 0);
	return (1);
}

int		main(int ac, char **av)
{
	t_wolf	wolf;
	t_mlx	*mlx;

	mlx = &wolf.mlx;
	if (ac != 2)
		display_usage();
	else
	{
		init_mlx_struct(&wolf);
		init_mlx(mlx);
		init_wolf(&wolf);
		parse_map(av[1], &wolf);
		get_segments(&wolf);
		get_points(&wolf);
		open_window(mlx);
		enable_key_events(&wolf);
		new_window_image(mlx);
		mlx_hook(mlx->window, RED_CROSS, 0, &close_program, (void*)mlx);
		mlx_loop_hook(mlx->connect, &main_loop, (void*)&wolf);
		mlx_loop(mlx->connect);
		free_everything(&wolf);
	}
	return (0);
}
