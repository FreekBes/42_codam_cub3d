/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/13 22:14:56 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_game game, char *error_msg)
{
	mouse_show_hide(&game, 0);
	if (error_msg)
		print_error(error_msg);
	free_map(game.mlx->core, game.map);
	free_mlx_context(game.mlx);
	if (game.cam.z_buffer)
		free(game.cam.z_buffer);
	exit(0);
	return (0);
}

static int	exit_hook(t_game *game)
{
	return (exit_game(*game, NULL));
}

static void	init_game_win(t_game *game)
{
	reset_key_presses(&game->key_stat);
	mouse_show_hide(game, 1);
	move_mouse(game, game->map->res_x / 2, game->map->res_y / 2);
	mlx_hook(game->mlx->win, 17, 1L << 17, &exit_hook, game);
	mlx_hook(game->mlx->win, 2, 1L << 0, &keypress, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, &keyrelease, game);
	mlx_hook(game->mlx->win, 4, 1L << 2, &mousebtnpress, game);
	mlx_hook(game->mlx->win, 6, 1L << 6, &mousemove, game);
	mlx_hook(game->mlx->win, 9, 1L << 21, &win_focus, game);
	mlx_loop_hook(game->mlx->core, draw_next_frame, game);
}

static int	setup_map(t_game *game, int save_bmp, char **argv)
{
	game->cam.speed_mod = 1;
	game->cam.mouse_sens = CAM_DEFAULT_MOUSE_SENSITIVITY;
	game->cam.z_buffer = NULL;
	game->map = parse_map(argv[1]);
	if (!game->map)
		return (print_error("Failed to read or parse map"));
	if (set_starting_pos(game) < 0)
		return (print_error("Start position in map is not set"));
	printf("start pos: %f, %f\n", game->cam.pos_x, game->cam.pos_y);
	if (!map_surrounded_by_walls(game))
		return (print_error("Map is not surrounded by walls"));
	if (save_bmp == 0)
		game->mlx = get_mlx_context(game->map, argv[0]);
	else
		game->mlx = get_mlx_context(game->map, NULL);
	if (!game->mlx)
		exit_game(*game, "Failed to create MLX instance");
	if (parse_textures(game) < 0)
		exit_game(*game, "Failed to parse textures, do the files exist?");
	parse_sprites(game);
	game->cam.z_buffer = (double *)malloc(sizeof(double) * game->map->res_x);
	if (!game->cam.z_buffer)
		exit_game(*game, "Could not allocate memory for z_buffer");
	print_map(*(game->map), NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game		game;
	int			save_bmp;

	save_bmp = 0;
	if (argc > 2 && ft_strncmp(argv[2], "--save", 7) == 0)
		save_bmp = 1;
	if (argc < 2)
		return (print_error("No map specified as first argument"));
	if (setup_map(&game, save_bmp, argv) == 0)
		return (0);
	if (save_bmp == 0)
	{
		init_game_win(&game);
		mlx_loop(game.mlx->core);
	}
	else
	{
		render_next_frame(&game);
		if (export_frame_as_bmp(&game, "cub3d.bmp") > 0)
			printf("Frame exported to cub3d.bmp\n");
		else
			exit_game(game, "Failed to export first frame as BMP");
	}
	return (exit_game(game, NULL));
}
