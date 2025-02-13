/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 18:32:19 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 16:01:54 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*
** KEYS
*/
# define ESCAPE_KEY 53
# define PLUS_SIGN 24
# define MINUS_SIGN 27
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_RIGHT 124
# define ARROW_LEFT 123
# define RED_CROSS 17
# define SHIFT_LEFT 257
# define SHIFT_RIGHT 258
# define ALT_LEFT 261
# define ALT_RIGHT 262
# define KEY_V 9
# define KEY_M 46
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_B 11
# define SPACEBAR 49
# define LEFT_COMMAND 259

/*
** MOUSE
*/
# define MOVE 6

/*
** PLAYER
*/

# define MIN_MOVE 0.19
# define DELTA_ANGLE 0.1
# define CATNIP_MOVE 0.49
# define DELTA_FOV 0.001

/*
**  COLOR
*/

# define YELLOW set_rgb(241, 233, 191)
# define RED set_rgb(194, 24, 7)
# define RED_2 set_rgb(224, 24, 7)
# define ORANGE set_rgb(255,170,70)
# define DARK_ORANGE set_rgb(156, 100, 79)
# define GRAY set_rgb(80, 80, 80)
# define BLUE set_rgb(0, 128, 255)
# define GREEN set_rgb(0, 128, 55)
# define WHITE set_rgb(255, 255, 255)
# define TRIPPY_VIOLET set_rgb(223, 0, 255)
# define TRIPPY_GREEN set_rgb(164, 222, 2)
# define COLOR_TRANSPARENT -16777216

# define MINIMAP_BORDER ORANGE
# define MINIMAP_GROUND GRAY
# define FILL_COLOR RED_2
# define POLYGON_COLOR RED

# define PLAYER_COLOR RED
# define MUSHROOM_COLOR set_rgb(204, 255, 0)
/*
** ERRORS
*/

# define FILE_READING_ERROR 0
# define GNL_ERROR 1
# define INVALID_CHAR 2
# define INVALID_LINE_LENGTH 3
# define TWO_STARTING_POSITION 4
# define NO_STARTING_POSITION 5
# define MALLOC_ERROR 6
# define INCORRECT_BORDER 7
# define MAP_TOO_BIG 8
# define IMAGE_ERROR 9
# define TOO_MUCH_OBJECTS 10

# define NB_ERRORS 11

# define THREAD_ERROR -1
# define TOO_FEW_TEXTURES -1

/*
** MAP CHARACTERS
*/

# define MAP_CHARS "0123456789XMBCR"
# define WALL_CHARS "123456789"
# define SPRITE_CHARS "MBCR"
# define MUSHROOM_CHAR 'M'
# define BARREL_CHAR 'B'
# define CATNIP_CHAR 'C'
# define CAT_ARMS_CHAR 'D'
# define CHAIR_CHAR 'R'
# define CAT_LEGS_CHAR 'L'
# define NUM_WALL_CHARS 10
# define PLAYER_CHAR 'X'
# define EMPTY_CHAR '0'

# define MUSHROOM MUSHROOM_CHAR
# define BARREL BARREL_CHAR
# define CATNIP CATNIP_CHAR
# define CHAIR CHAIR_CHAR
# define CAT_ARMS_ATTACK CAT_ARMS_CHAR
# define CAT_LEGS_ATTACK CAT_LEGS_CHAR

# define NB_SPRITES 7
# define MUSHROOM_SPRITE 0
# define BARREL_SPRITE 1
# define CAT_ARMS_SPRITE 2
# define CAT_LEGS_SPRITE 3
# define CATNIP_SPRITE 4
# define CHAIR_SPRITE 5
# define CHAIRHAIR_SPRITE 6

/*
** weapons
*/
# define ARM 1
# define LEGS 2

# define NB_TEXTURES 10
# define COLORSTONE_TEXTURE 0
# define LITTER_TEXTURE 1
# define RUG_TEXTURE 2
# define GRUMPY_TEXTURE 3
# define BRICK_TEXTURE 4
# define STONE_TEXTURE 5
# define WOOD_TEXTURE 6
# define BLUESTONE_TEXTURE 7
# define PURPLESTONE_TEXTURE 8
# define DRUG_TEXTURE 9

# define VARIOUS_TEXTURES '1'
# define GROUND_TEXTURE RUG_TEXTURE

# define MIN_HEIGHT_SPRITE 1

/*
** SPRITE SIZE
*/

# define BARREL_HEIGHT 600
# define BARREL_WIDTH 400
# define CATNIP_HEIGHT 500
# define CATNIP_WIDTH 500
# define MUSHROOM_HEIGHT 450
# define MUSHROOM_WIDTH 300
# define CHAIR_HEIGHT 1200
# define CHAIR_WIDTH 700

/*
** MLX EVENTS
*/

# define KEY_PRESS 2
# define KEY_RELEASE 3

/*
** default values
*/

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define DEFAULT_SQUARE_SIDE 6

/*
** OTHER
*/

# define DRUG_DURATION 1000
# define DISTANCE_PICK_UP 0.7
# define HALF 2.0
# define MAP_H 150
# define MAP_W 80

# define NB_MAX_OBJECTS 3000

# define EPSILON_PRECISION 0.0001
# define EPSILON_ANGLE 0.0001

# define PRECISION_FACTOR_RAYCASTING 30

# define INITIAL_PLAYER_ANGLE 0.001

# define NORMAL_FIELD_OF_VIEW M_PI / 4
# define MAX_FOV M_PI * 1.8
# define MIN_FOV M_PI / 64

#endif
