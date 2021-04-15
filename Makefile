NAME =		cub3D

SRCS =		main.c src/printer.c src/map_parser.c src/window.c src/drawer.c src/colors.c

OBJS =		$(SRCS:.c=.o)

CFLAGS =

UNAME =		$(shell uname)

all: $(NAME)

$(NAME): $(OBJS) libft mlx
ifeq ($(UNAME), Linux)
	$(CC) $(SRCS) lib/libft/libft.a lib/mlx_lin/libmlx.a -lXext -lX11 -lm -lz -fsanitize=address -o $(NAME)
else
	$(CC) $(SRCS) lib/libft/libft.a lib/mlx/libmlx.a -framework OpenGL -framework AppKit -fsanitize=address -o $(NAME)
endif

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

libft: FORCE
	make -C lib/libft

mlx: FORCE
ifeq ($(UNAME), Linux)
	make -C lib/mlx_lin
else
	make -C lib/mlx
endif

FORCE:

clean:
	rm -f $(OBJS)
	make -C lib/libft clean
	make -C lib/mlx clean
	make -C lib/mlx_lin clean

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C lib/libft fclean
	make -C lib/mlx clean
	make -C lib/mlx_lin clean

re: fclean all

.PHONY: all clean fclean re mlx FORCE
