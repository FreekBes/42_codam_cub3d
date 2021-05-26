/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/26 19:52:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_game *game, int exit_code, char *error_msg, char *m_error_msg)
{
	if (game->bmp_export == 0)
	{
		mouse_show_hide(game, 0);
		if (game->mlx)
			mlx_do_key_autorepeaton(game->mlx->core);
	}
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
	mlx_do_key_autorepeatoff(game->mlx->core);
	move_mouse(game, game->map->res_x / 2, game->map->res_y / 2);
	mlx_hook(game->mlx->win, 17, 1L << 17, &exit_hook, game);
	mlx_hook(game->mlx->win, 2, 1L << 0, &keypress, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, &keyrelease, game);
	mlx_hook(game->mlx->win, 4, 1L << 2, &mousebtnpress, game);
	mlx_hook(game->mlx->win, 6, 1L << 6, &mousemove, game);
	mlx_expose_hook(game->mlx->win, win_focus, game);
	mlx_loop_hook(game->mlx->core, draw_next_frame, game);
}

int	main(int argc, char **argv)
{
	t_game		game;

	errno = 0;
	setup_args(argc, argv, &game);
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
