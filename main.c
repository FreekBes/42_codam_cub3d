/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/17 19:02:23 by fbes          ########   odam.nl         */
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
		return (print_error(ERR_MAP_READ_PARSE));
	if (set_starting_pos(game) < 0)
		return (print_error(ERR_START_POS));
	if (!map_surrounded_by_walls(game))
		return (print_error(ERR_MAP_WALLS_MISSING));
	if (save_bmp == 0)
		game->mlx = get_mlx_context(game->map, argv[0]);
	else
		game->mlx = get_mlx_context(game->map, NULL);
	if (!game->mlx)
		exit_game(*game, ERR_CREATE_MLX_CONTEXT);
	if (parse_textures(game) < 0)
		exit_game(*game, ERR_TEXTURE_PARSE);
	parse_sprites(game);
	game->cam.z_buffer = (double *)malloc(sizeof(double) * game->map->res_x);
	if (!game->cam.z_buffer)
		exit_game(*game, ERR_Z_BUFFER_ALLOC);
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
		return (print_error(ERR_MAP_MISSING));
	if (setup_map(&game, save_bmp, argv) != 1)
		return (0);
	if (save_bmp == 0)
	{
		init_game_win(&game);
		mlx_loop(game.mlx->core);
	}
	else
	{
		render_next_frame(&game);
		if (export_frame_as_bmp(&game, "cub3d.bmp") != 1)
			exit_game(game, ERR_BMP_EXPORT);
	}
	return (exit_game(game, NULL));
}
