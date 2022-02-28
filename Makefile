# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/21 20:02:11 by fbes          #+#    #+#                  #
#    Updated: 2022/02/28 20:37:16 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		cub3D

SRCS =		main.c src/helpers.c src/printer.c src/map.c src/map_reader.c \
			src/level_parser.c src/map_parser.c src/map_checker.c \
			src/wall_checker_utils.c src/wall_checker.c src/simple_checks.c \
			src/drawer.c src/textures.c src/start_pos.c \
			src/colors.c src/sprites.c src/renderer_sprites.c \
			src/renderer_inits.c src/renderer_walls.c src/renderer.c \
			src/camera.c src/controls.c src/mouse.c src/window.c \
			src/errors.c src/color_mods.c src/setup.c

INCLUDES =	-I lib/libft -I includes -I lib/MLX42/include

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra -Ofast

all: $(NAME)

$(NAME): $(OBJS) lib/libft/libft.a lib/MLX42/libmlx42.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) \
	lib/libft/libft.a lib/MLX42/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

lib/libft/libft.a:
	make -C lib/libft

lib/MLX42/libmlx42.a:
	make -C lib/MLX42

bonus: all

clean:
	rm -f $(OBJS)
	make -C lib/libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C lib/libft fclean
	make -C lib/MLX42 fclean

re: fclean all

.PHONY: all clean fclean re bonus FORCE
