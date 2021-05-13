# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/21 20:02:11 by fbes          #+#    #+#                  #
#    Updated: 2021/05/13 21:53:12 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		cub3D

OS_SRCS =	src/main.c src/mouse.c

SRCS =		src/helpers.c src/printer.c src/map.c src/map_reader.c \
			src/level_parser.c src/map_parser.c src/map_checker.c \
			src/wall_checker_utils.c src/wall_checker.c src/window.c \
			src/drawer.c src/export.c src/textures.c src/start_pos.c \
			src/colors.c src/sprites.c src/renderer_sprites.c \
			src/renderer_inits.c src/renderer_walls.c src/renderer.c \
			src/camera.c src/controls.c src/main.c src/mouse.c

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

UNAME =		$(shell uname)

all: $(NAME)

$(NAME): oscopy $(OBJS) libft mlx
ifeq ($(UNAME), Linux)
	$(CC) $(SRCS_L) $(SRCS) lib/libft/libft.a lib/mlx_lin/libmlx.a -lXext -lX11 -lm -lz -fsanitize=address -o $(NAME)
else
	$(CC) $(SRCS_M) $(SRCS) lib/libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit -fsanitize=address -o $(NAME)
endif

.c.o:
ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
else
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
endif

libft: FORCE
	make -C lib/libft

mlx: FORCE
ifeq ($(UNAME), Linux)
	make -C lib/mlx_lin
else
	make -C lib/mlx
	mv lib/mlx/libmlx.dylib libmlx.dylib
endif

oscopy: FORCE
ifeq ($(UNAME), Linux)
	cp -r -f src/lin/ src
else
	cp -r -f src/mac/ src
endif

FORCE:

clean:
	rm -f $(OS_SRCS) $(OBJS)
	make -C lib/libft clean
	make -C lib/mlx clean
	make -C lib/mlx_lin clean

fclean:
	rm -f $(OS_SRCS) $(OBJS) $(NAME)
	make -C lib/libft fclean
ifeq ($(UNAME), Linux)
	make -C lib/mlx_lin clean
else
	make -C lib/mlx clean
	rm -f libmlx.dylib
endif

re: fclean all

.PHONY: all clean fclean re mlx libft oscopy FORCE
