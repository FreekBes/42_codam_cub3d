# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/21 20:02:11 by fbes          #+#    #+#                  #
#    Updated: 2021/10/28 20:58:39 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		cub3D

UNAME =		$(shell uname)

ifeq ($(UNAME), Linux)

SRCS =		main.c src/helpers.c src/printer.c src/map.c src/map_reader.c \
			src/level_parser.c src/map_parser.c src/map_checker.c \
			src/wall_checker_utils.c src/wall_checker.c src/simple_checks.c \
			src/drawer.c src/export.c src/textures.c src/start_pos.c \
			src/colors.c src/sprites.c src/renderer_sprites.c \
			src/renderer_inits.c src/renderer_walls.c src/renderer.c \
			src/camera.c src/controls.c src/lin/mouse.c src/window.c \
			src/errors.c src/color_mods.c src/setup.c

INCLUDES =	-Ilib/libft -Iincludes -Ilib/mlx_lin

else

SRCS =		main.c src/helpers.c src/printer.c src/map.c src/map_reader.c \
			src/level_parser.c src/map_parser.c src/map_checker.c \
			src/wall_checker_utils.c src/wall_checker.c src/simple_checks.c \
			src/drawer.c src/export.c src/textures.c src/start_pos.c \
			src/colors.c src/sprites.c src/renderer_sprites.c \
			src/renderer_inits.c src/renderer_walls.c src/renderer.c \
			src/camera.c src/controls.c src/mac/mouse.c src/window.c \
			src/errors.c src/color_mods.c src/setup.c

INCLUDES =	-I lib/libft -I includes -I lib/mlx

endif

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) lib/libft/libft.a libmlx.dylib
ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) \
	lib/libft/libft.a lib/mlx_lin/libmlx.a -lXext -lX11 -lm -lz -o $(NAME)
else
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) \
	lib/libft/libft.a libmlx.dylib -o $(NAME)
endif

.c.o:
ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
else
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
endif

lib/libft/libft.a:
	make -C lib/libft

libmlx.dylib:
ifeq ($(UNAME), Linux)
	make -C lib/mlx_lin
else
	make -C lib/mlx
	test -L libmlx.dylib || ln -sf lib/mlx/libmlx.dylib libmlx.dylib
endif

bonus: all

clean:
	rm -f $(OBJS)
	make -C lib/libft clean
	make -C lib/mlx clean
	make -C lib/mlx_lin clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C lib/libft fclean
ifeq ($(UNAME), Linux)
	make -C lib/mlx_lin clean
else
	make -C lib/mlx clean
	rm -f libmlx.dylib
endif

re: fclean all

.PHONY: all clean fclean re mlx libft bonus FORCE
