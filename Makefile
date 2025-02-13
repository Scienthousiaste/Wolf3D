# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 11:38:21 by tbehra            #+#    #+#              #
#    Updated: 2019/09/13 16:54:03 by tbehra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra
THREAD = -lpthread

NAME	= wolf3d

SRCDIR	= src
OBJDIR	= obj
INCDIR	= include

SRC	= main.c parse_map.c mlx.c errors.c small_functions.c init.c	\
	 update_player_position.c raycasting.c lines.c					\
	   segments_get.c segments_count.c segments_helpers.c			\
	  segments.c drug.c minimap.c sprites.c trace_line.c 			\
	  images.c view.c angles.c points.c textures.c objects.c 		\
	  texture_change.c init_mlx.c sort_objects.c  					\
      insert_intersection.c draw.c free.c get_visible_segments.c	\
	  mlx_key_events.c special_sprites.c map_checks.c

HEAD	= wolf.h defines.h structs.h

LIBDIR	= libft
LIBFT	= $(LIBDIR)/libft.a

OBJ		= $(SRC:.c=.o)

HEADP	= $(addprefix $(INCDIR)/, $(HEAD))
OBJP	= $(addprefix $(OBJDIR)/, $(OBJ))
INCP	= $(foreach dir, $(INCDIR), -I$(dir))

MLXP	= -I ./minilibx  $(THREAD)
MLX		= -L ./minilibx -lmlx -framework OpenGL -framework AppKit

all: $(LIBFT) $(OBJDIR) $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADP)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(LIBDIR) $(INCP)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make all -C $(LIBDIR)

$(NAME): $(LIBFT) $(OBJP)
	$(CC) $(CFLAGS) -o $@ $^ -I$(LIBDIR) $(MLXP) $(MLX)

clean:
	make clean -C $(LIBDIR)
	rm -rf $(OBJDIR)

fclean:
	make fclean -C $(LIBDIR)
	rm -rf $(OBJDIR)
	rm -f $(NAME)
