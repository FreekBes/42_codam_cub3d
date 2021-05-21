/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/21 14:00:39 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_game *game, int exit_code, char *error_msg, char *m_error_msg)
{
	if (game->bmp_export == 0)
		mouse_show_hide(game, 0);
	if (error_msg && !m_error_msg)
		print_error(error_msg);
	if (m_error_msg)
	{
		print_error(m_error_msg);
		ft_free(m_error_msg);
	}
	if (game->mlx)
	{
		if (game->map)
			free_map(game->mlx->core, game->map);
		free_mlx_context(game->mlx);
	}
	else if (game->map)
		free_map(NULL, game->map);
	if (game->cam.z_buffer)
		free(game->cam.z_buffer);
	exit(exit_code);
	return (exit_code);
}

static int	exit_hook(t_game *game)
{
	return (exit_game(game, 0, NULL, NULL));
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
	mlx_expose_hook(game->mlx->win, win_focus, game);
	mlx_loop_hook(game->mlx->core, draw_next_frame, game);
}

static void	setup_map(t_game *game, int save_bmp, char **argv)
{
	int		err;

	game->cam.speed_mod = 1;
	game->cam.mouse_sens = CAM_DEFAULT_MOUSE_SENSITIVITY;
	game->cam.z_buffer = NULL;
	game->map = parse_map(argv[1], &err);
	if (!game->map)
		exit_game(game, ft_abs(err), NULL, get_config_error(&err));
	if (set_starting_pos(game) < 0)
		exit_game(game, 100, ERR_START_POS, NULL);
	if (!map_surrounded_by_walls(game))
		exit_game(game, 101, ERR_MAP_WALLS_MISSING, NULL);
	if (save_bmp == 0)
		game->mlx = get_mlx_context(game->map, argv[0]);
	else
		game->mlx = get_mlx_context(game->map, NULL);
	if (!game->mlx)
		exit_game(game, 102, ERR_CREATE_MLX_CONTEXT, NULL);
	err = parse_textures(game);
	if (err < 0)
		exit_game(game, ft_abs(err), ERR_TEXTURE_PARSE, get_config_error(&err));
	parse_sprites(game);
	game->cam.z_buffer = (double *)malloc(sizeof(double) * game->map->res_x);
	if (!game->cam.z_buffer)
		exit_game(game, 104, ERR_Z_BUFFER_ALLOC, NULL);
}

int	main(int argc, char **argv)
{
	t_game		game;

	errno = 0;
	game.bmp_export = 0;
	if (argc > 2 && ft_strncmp(argv[2], "--save", 7) == 0)
		game.bmp_export = 1;
	if (argc < 2)
		return (print_error(ERR_CONF_MISSING));
	setup_map(&game, game.bmp_export, argv);
	if (game.bmp_export == 0)
	{
		init_game_win(&game);
		mlx_loop(game.mlx->core);
	}
	else
	{
		render_next_frame(&game);
		if (export_frame_as_bmp(&game, "cub3d.bmp") != 1)
			exit_game(&game, 105, ERR_BMP_EXPORT, NULL);
	}
	return (exit_game(&game, 0, NULL, NULL));
}
