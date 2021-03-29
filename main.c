/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/29 21:07:19 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	if (map->tex_no)
		free(map->tex_no);
	if (map->tex_so)
		free(map->tex_so);
	if (map->tex_we)
		free(map->tex_we);
	if (map->tex_ea)
		free(map->tex_ea);
	if (map->col_ceiling)
		free(map->col_ceiling);
	if (map->col_floor)
		free(map->col_floor);
	free(map);
}

static int	print_error(char *msg)
{
	printf("Error\n%s\n", msg);
	strerror(errno);
	return (-1);
}

static void	print_color(t_col_rgba color)
{
	printf("R%i, G%i, B%i, A%i", (int)color.r, (int)color.g,
		(int)color.b, (int)color.a);
}

static void	print_map(t_map map)
{
	printf("res_x: %i\nres_y: %i\n", (int)map.res_x, (int)map.res_y);
	printf("tex_no: %s\ntex_so: %s\n", map.tex_no, map.tex_so);
	printf("tex_we: %s\ntex_ea: %s\n", map.tex_we, map.tex_ea);
	printf("tex_sprite: %s\ncol_floor: ", map.tex_sprite);
	print_color(*(map.col_floor));
	printf("\ncol_ceiling: ");
	print_color(*(map.col_ceiling));
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_mlx_ctx	*mlx_ctx;

	if (argc < 2)
		return (print_error("No map specified as first argument"));
	map = parse_map(argv[1]);
	if (!map)
		return (print_error("Failed to parse map"));
	print_map(*map);
	mlx_ctx = get_mlx_context(map, argv[0]);
	if (!mlx_ctx)
		return (print_error("Failed to open MLX window"));
	mlx_loop(mlx_ctx->core);
	free_map(map);
	free_mlx_context(mlx_ctx);
	exit(0);
}
