/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/31 16:06:53 by fbes          ########   odam.nl         */
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

static int	exit_game(t_game game, char *error_msg)
{
	if (error_msg)
		print_error(error_msg);
	free_mlx_context(game.mlx);
	free_map(game.map);
	//system("leaks cub3D");
	exit(0);
	return (0);
}

static int	exit_hook(t_game *game)
{
	return (exit_game(*game, NULL));
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc < 2)
		return (print_error("No map specified as first argument"));
	game.map = parse_map(argv[1]);
	if (!game.map)
		return (print_error("Failed to parse map"));
	print_map(*(game.map));
	game.mlx = get_mlx_context(game.map, argv[0]);
	if (!game.mlx)
		exit_game(game, "Failed to open MLX window");
	mlx_hook(game.mlx->win, 17, 0, &exit_hook, &game);
	put_pixel(game.mlx->img, 10, 10, color_to_uint(*(game.map->col_ceiling)));
	mlx_put_image_to_window(game.mlx->core, game.mlx->win,
		game.mlx->img->img_ptr, 0, 0);
	mlx_loop(game.mlx->core);
	return (exit_game(game, NULL));
}
