NAME =		cub3D

SRCS =		main.c src/printer.c src/map_parser.c src/window.c src/drawer.c src/colors.c

OBJS =		$(SRCS:.c=.o)

CFLAGS =

all: $(NAME)

$(NAME): $(OBJS) lib/libft/libft.a lib/mlx/libmlx.a
	$(CC) $(SRCS) lib/libft/libft.a lib/mlx/libmlx.a -framework OpenGL -framework AppKit -fsanitize=address -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

lib/libft/libft.a: FORCE
	make -C lib/libft

lib/mlx/libmlx.a: FORCE
	make -C lib/mlx

FORCE:

clean:
	rm -f $(OBJS)
	make -C lib/libft clean
	make -C lib/mlx clean

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C lib/libft fclean
	make -C lib/mlx clean

re: fclean all

.PHONY: all clean fclean re FORCE
