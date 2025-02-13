/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:14:21 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 16:28:58 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_map(t_wolf *wolf, int number_lines)
{
	t_map *map;

	map = &wolf->map;
	map->width = 0;
	map->height = number_lines;
	if (!(map->array = (int**)malloc(sizeof(int*) * map->height)))
		parsing_error(MALLOC_ERROR, 0);
	map->objects = NULL;
}

void	init_player(t_player *player)
{
	ft_bzero(player, sizeof(player));
	player->position.x = NAN;
	player->position.y = NAN;
	player->angle = INITIAL_PLAYER_ANGLE;
	player->direction.x = cos(player->angle);
	player->direction.y = sin(player->angle);
	player->velocity = MIN_MOVE;
	player->running_multiple = 1;
	player->is_pivoting = 0;
	player->is_moving = 0;
	player->is_strafing = 0;
	player->is_attacking = FALSE;
	player->weapon = ARM;
	player->field_of_view = NORMAL_FIELD_OF_VIEW;
	player->is_under_influence = 0;
	player->is_catniped = 0;
	player->drug_stop = 0;
	player->display_minimap = FALSE;
}

void	init_sprites(t_wolf *wolf)
{
	if (!(wolf->sprites = (t_img*)malloc(sizeof(t_img) * NB_SPRITES)))
		exit_on_error(MALLOC_ERROR);
	wolf->sprites[MUSHROOM_SPRITE] = make_img(wolf, "sprites/mushroom.xpm");
	wolf->sprites[BARREL_SPRITE] = make_img(wolf, "sprites/barrel.xpm");
	wolf->sprites[CAT_ARMS_SPRITE] =
		make_img(wolf, "sprites/cat_arm_small.xpm");
	wolf->sprites[CAT_LEGS_SPRITE] = make_img(wolf, "sprites/cat_legs.xpm");
	wolf->sprites[CATNIP_SPRITE] = make_img(wolf, "sprites/catnip.xpm");
	wolf->sprites[CHAIR_SPRITE] = make_img(wolf, "sprites/chair.xpm");
	wolf->sprites[CHAIRHAIR_SPRITE] = make_img(wolf, "sprites/chair_hair.xpm");
}

void	init_textures(t_wolf *wolf)
{
	if (NB_TEXTURES < 4)
		exit_on_error(TOO_FEW_TEXTURES);
	if (!(wolf->textures = (t_img*)malloc(sizeof(t_img) * NB_TEXTURES)))
		exit_on_error(MALLOC_ERROR);
	wolf->textures[GRUMPY_TEXTURE] = make_img(wolf, "textures/grumpy.xpm");
	wolf->textures[STONE_TEXTURE] = make_img(wolf, "textures/greystone.xpm");
	wolf->textures[BRICK_TEXTURE] = make_img(wolf, "textures/redbrick.xpm");
	wolf->textures[WOOD_TEXTURE] = make_img(wolf, "textures/wood.xpm");
	wolf->textures[BLUESTONE_TEXTURE] = make_img(wolf,
			"textures/bluestone.xpm");
	wolf->textures[PURPLESTONE_TEXTURE] = make_img(wolf,
			"textures/purplestone.xpm");
	wolf->textures[COLORSTONE_TEXTURE] = make_img(wolf,
			"textures/colorstone.xpm");
	wolf->textures[LITTER_TEXTURE] = make_img(wolf, "textures/litter.xpm");
	wolf->textures[RUG_TEXTURE] = make_img(wolf, "textures/rug.xpm");
	wolf->textures[DRUG_TEXTURE] = make_img(wolf, "textures/drogues.xpm");
}

void	init_wolf(t_wolf *wolf)
{
	init_player(&wolf->player);
	init_sprites(wolf);
	init_textures(wolf);
	wolf->visible_segments = NULL;
	wolf->intersections = NULL;
	wolf->frame_counter = 0;
	wolf->color_ceilling = BLUE;
	wolf->color_ground = GREEN;
	srand(time(NULL));
}
