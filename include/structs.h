/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:39:03 by tbehra            #+#    #+#             */
/*   Updated: 2019/09/13 15:26:49 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef enum				e_bool
{
	FALSE,
	TRUE
}							t_bool;

typedef enum				e_orient
{
	LEFT,
	RIGHT,
	UP,
	DOWN
}							t_orient;

typedef struct				s_point
{
	double					x;
	double					y;
}							t_point;

typedef struct				s_segment
{
	t_point					start;
	t_point					end;
	int						texture;
	t_orient				orientation;
}							t_segment;

typedef struct				s_pixel
{
	int						x;
	int						y;
}							t_pixel;

typedef struct				s_couple
{
	int						a;
	int						b;
}							t_couple;

typedef struct				s_draw_data
{
	t_point					prop;
	t_pixel					offset;
	t_pixel					size_on_screen;
	t_pixel					sprite_pixel;
	int						color;
	int						max_y;
}							t_draw_data;

typedef struct				s_point_option
{
	t_point					p;
	t_bool					found;
}							t_point_option;

typedef struct				s_half_line
{
	double					slope;
	double					intercept;
	t_point					direction;
	t_point					origin;
}							t_half_line;

typedef struct				s_player
{
	t_point					position;
	t_point					direction;
	double					angle;
	t_bool					is_attacking;
	t_bool					display_minimap;
	double					velocity;
	double					field_of_view;
	int						is_moving;
	int						is_pivoting;
	int						is_strafing;
	int						running_multiple;
	int						is_under_influence;
	int						is_catniped;
	int						weapon;
	size_t					drug_stop;
}							t_player;

typedef struct				s_mlx
{
	mlx_t					*mlx;
	char					*window_name;
	int						window_height;
	int						window_width;
	uint8_t					*window_image;
	mlx_image_t				*img_ptr;
	int						img_size_line;
}							t_mlx;

typedef struct				s_img
{
	mlx_image_t				*image;
	uint8_t					*img_ptr;
	int						height;
	int						width;
}							t_img;

typedef struct				s_points_list
{
	t_point					p;
	t_segment				*segment;
	struct s_points_list	*next;
	double					angle;
}							t_points_list;

typedef struct				s_object
{
	struct s_object			*next;
	t_img					*sprite;
	t_point					position;
	double					distance;
	char					type;
	int						height;
	int						width;
}							t_object;

typedef struct				s_map
{
	int						**array;
	t_segment				*segments;
	t_points_list			*unique_points;
	t_points_list			*intersections;
	t_object				*objects;
	size_t					height;
	size_t					width;
	size_t					offset_x;
	size_t					offset_y;
	size_t					square_side;
	size_t					segments_length;
	int						line_size;
}							t_map;

typedef struct				s_wall_list
{
	t_segment				wall;
	double					distance;
	struct s_wall_list		*next;
}							t_wall_list;

typedef struct				s_wolf
{
	t_map					map;
	t_player				player;
	t_mlx					mlx;
	t_img					*sprites;
	t_img					*textures;
	t_wall_list				*visible_segments;
	t_points_list			*intersections;
	t_point					first_intersection;
	t_point					last_intersection;
	size_t					frame_counter;
	int						color_ceilling;
	int						color_ground;
	double					smallest_distance_to_wall;
}							t_wolf;

#endif
