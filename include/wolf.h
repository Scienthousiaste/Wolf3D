/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmurte <jmurte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:53:38 by jmurte            #+#    #+#             */
/*   Updated: 2019/09/13 15:27:51 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/*
** for bonus
*/
# include <math.h>
# include <time.h>
# include <pthread.h>

# include "defines.h"
# include "structs.h"

/*
** minilibx
*/

void				enable_key_events(t_wolf *wolf);
void				open_window(t_mlx *mlx);
void				new_window_image(t_mlx *mlx);
void				close_program(void *param);
int					key_press_handler(int keycode, t_wolf *wolf);
int					key_press_handle_attack(int keycode, t_wolf *wolf);
int					key_release_handler(int keycode, t_wolf *wolf);
int					key_press_handle_minimap(int keycode, t_wolf *wolf);
int					set_rgb(int red, int green, int blue);
void				*meow_thread();

/*
** parsing
*/

int					parse_map(char *filename, t_wolf *wolf);
void				check_correct_borders(char *line, t_map *map,
						size_t line_number);
void				check_only_correct_chars(char *line, int line_number);
int					check_if_map_is_too_big(t_wolf *wolf);

/*
** errors
*/

void				parsing_error(int error, int line_number);
void				exit_on_error(int error);
void				display_usage(void);

/*
** init
*/

void				init_wolf(t_wolf *wolf);
void				init_map(t_wolf *wolf, int number_lines);
void				init_player(t_player *player);
void				init_mlx(t_mlx *mlx);
void				init_mlx_struct(t_wolf *wolf);
void				player_init(t_wolf *wolf, int i, int j);

/*
** catnip
*/

void				start_mushroom_effects(t_wolf *wolf);
void				start_catnip_effects(t_wolf *wolf);
void				check_events(t_wolf *wolf);

/*
** minimap
*/

void				draw_minimap(t_wolf *wolf);
void				draw_player(t_wolf *wolf);
void				draw_square(t_mlx *mlx, t_point *begin,
						size_t square_side, int color);
void				draw_player_view_minimap(t_wolf *wolf);
void				draw_visibility_polygon(t_wolf *wolf);
void				put_pixel_image(t_mlx *mlx, t_pixel p, int color);
int					is_ground_pixel(t_wolf *wolf, t_pixel p);
int					get_pixel_window(t_mlx *mlx, t_pixel p);
t_pixel				position_to_minimap_pixel(t_wolf *wolf, t_point pos);
t_pixel				make_pixel(int x, int y);
t_couple			couple(int a, int b);
t_point				make_point(double x, double y);
t_segment			make_segment(t_point start, t_point end, int texture,
						t_orient orientation);

/*
** update_player_position
*/

void				update_player(t_wolf *wolf);
void				update_player_direction(t_wolf *wolf, double angle_delta);
void				update_player_position(t_wolf *wolf, t_point direction,
						double move);

/*
** segments
*/

size_t				count_vertical_segments(t_map *map, t_pixel p);
size_t				count_horizontal_segments(t_map *map, t_pixel p);
int					reinit_segment(t_segment *s);
int					set_segment(t_segment *s, int texture, int orientation,
						t_point start);
void				get_segments(t_wolf *wolf);
int					is_wall(t_map *map, int i, int j);
int					is_same(t_map *map, int i, int j, int k, int l);
int					new_wall_to_non_wall(t_map *map, t_pixel p,
						int start_segment, t_bool horizontal);
int					was_wall_to_non_wall(t_map *map, t_pixel p,
						int start_segment, t_bool horizontal);
int					new_non_wall_to_wall(t_map *map, t_pixel p,
						int start_segment, t_bool horizontal);
int					was_non_wall_to_wall(t_map *map, t_pixel p,
						int start_segment, t_bool horizontal);
int					w_to_nw_texture_change(t_map *map, t_pixel p, t_segment s,
						t_bool horizontal);
int					nw_to_w_texture_change(t_map *map, t_pixel p, t_segment s,
						t_bool horizontal);
int					texture_change(t_map *map, t_pixel p, int start_segment,
						t_bool horizontal);
int					is_same_segment(t_segment s, t_segment ss);
void				copy_segment_in(t_segment *src, t_segment *dest);

/*
** raycasting
*/

t_point_option		find_intersection(t_half_line ray, t_segment wall);
t_point_option		find_closest_intersection(t_wolf *wolf, t_half_line ray);
t_points_list		find_closest_segment_intersection(t_wolf *wolf,
						t_half_line ray, t_bool *found);

/*
** view
*/
void				draw_player_vision(t_wolf *wolf, int x_column,
						t_point closest_intersect_point, t_wall_list *cur_wall);
int					is_not_in_segments(t_wall_list *walls,
						t_segment *current_wall);

/*
** visible segments
*/

void				make_visible_segments(t_wolf *wolf);
void				get_visible_segments(t_wolf *wolf,
						t_points_list *extremity);

/*
** traceline
*/

int					trace_line(t_wolf *wolf, t_pixel start, t_pixel end,
						int color);
t_bool				find_in_line(t_wolf *wolf, t_pixel start,
						t_pixel end, int color);

/*
** points
*/

void				get_points(t_wolf *wolf);
t_bool				is_same_point(t_point p1, t_point p2);
int					is_not_in(t_point p, t_points_list *unique_points,
						t_segment s);
t_points_list		*add_to_list(t_points_list **points_list, t_point point,
						t_segment *segment);
t_point				insert_intersection(t_wolf *wolf, t_point intersection,
						t_segment *segment, double angle);
void				free_points_list(t_points_list **points_list);

/*
** sprites
*/

void				draw_sprites(t_wolf *wolf);
t_img				*get_sprite(char type, t_wolf *wolf);
t_img				make_img(t_wolf *wolf, char *file);
void				draw_cat_sprite(t_wolf *wolf);
void				draw_cat_arm_sprite(t_wolf *wolf, t_img *sprite);
void				draw_cat_legs_sprite(t_wolf *wolf, t_img *sprite);
void				put_cat_arm_in_img(t_wolf *wolf, t_img *sprite,
						int offset_x, int offset_y);
void				put_cat_legs_in_img(t_wolf *wolf, t_img *sprite);

int					sprite_too_big(t_wolf *wolf, int offset_x, int offset_y,
						t_img *sprite);

/*
** textures
*/

int					get_texture_color(t_img *texture, t_segment *wall,
						t_point *intersect, double prop_y);
int					get_color_from_orientation(t_orient orientation);
int					get_color_wall_pixel(t_wolf *wolf, t_segment wall,
						t_point intersect, double prop_y);

/*
** objects
*/

void				print_objects(t_object *objects);
void				add_object(t_wolf *wolf, char type, t_point position);
int					get_height(char type, t_img *sprite);
int					get_width(char type, t_img *sprite);

size_t				count_objects(t_object *object);
void				sort_objects(t_object **objects, t_wolf *wolf);
void				compute_object_distances(t_object *objects, t_wolf *wolf);

/*
** angles
*/

double				angle_between(t_point a, t_point b);
int					is_in_fov(t_wolf *wolf, t_point position);
int					is_in_fov_angle(t_wolf *wolf, t_point position);
int					no_obstacle(t_wolf *wolf, t_point target, double angle);

/*
** lines
*/

t_half_line			make_half_line(t_point origin, t_point direction);
double				distance(t_point p1, t_point p2);
double				perpendicular_distance(t_segment wall, t_point player_pos,
						t_point intersect, t_half_line ray);
t_bool				is_point_on_half_line(t_point p, t_half_line line);
t_bool				is_on_side_of_half_line(t_point p, t_half_line line);

void				player_gaze(t_wolf *wolf);
int					radians_to_degrees(double radians);
double				degrees_to_radians(double degrees);
void				draw_floor_ceilling_wall(t_wolf *wolf, int x,
double				distance_to_wall, t_segment wall);
void				draw_column(t_wolf *wolf, int x, t_segment wall,
						t_point intercept);
double				intersection_ray_wall(t_wolf *wolf,
						double distance_to_wall);

#endif
