/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/06/14 22:23:21 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "MLX42/MLX42.h"
#include "c3d.h"
#include "c3d_game_errors.h"

int	exit_game(t_game *game, int exit_code, char *error_msg, char *m_error_msg)
{
	if (game->bmp_export == 0 && game->mlx)
		mlx_set_cursor_mode(game->mlx->core, MLX_MOUSE_NORMAL);
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
			free_map(game->map);
		mlx_quit(game->mlx->core);
		mlx_terminate(game->mlx->core);
	}
	else if (game->map)
		free_map(game->map);
	if (game->cam.z_buffer)
		free(game->cam.z_buffer);
	exit(exit_code);
	return (exit_code);
}

static void	exit_hook(t_keys key, t_action action, void *game)
{
	if (key == MLX_KEY_ESCAPE && action == MLX_PRESS)
		exit_game((t_game *)game, 0, NULL, NULL);
}

static void	init_game_win(t_game *game)
{
	mlx_set_cursor_mode(game->mlx->core, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->mlx->core, game->map->res_x / 2, game->map->res_y / 2);
	mlx_key_hook(game->mlx->core, &exit_hook, game);
	// mlx_hook(game->mlx->win, 17, 1L << 17, &exit_hook, game);
	mlx_scroll_hook(game->mlx->core, &mousescrollwheel, game);
	// mlx_hook(game->mlx->win, 6, 1L << 6, &mousemove, game);
	// mlx_expose_hook(game->mlx->win, win_focus, game);
	mlx_loop_hook(game->mlx->core, draw_next_frame, game);
}

int	main(int argc, char **argv)
{
	t_game		game;

	errno = 0;
	init_game(&game);
	setup_args(argc, argv, &game);
	setup_game(&game, argv);
	init_game_win(&game);
	mlx_loop(game.mlx->core);
	return (exit_game(&game, 0, NULL, NULL));
}
