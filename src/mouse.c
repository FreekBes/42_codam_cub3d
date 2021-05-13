/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:04:23 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/13 20:29:53 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	win_focus(t_game *game)
{
	mlx_mouse_move(OS_MLX_REQ_PARAMS, game->map->res_x / 2,
		game->map->res_y / 2);
	return (1);
}

// mlx_mouse_get_pos is used below to get the latest mouse position, as the
// parameters int x and int y are sometimes slightly behind

int	mousemove(int x, int y, t_game *game)
{
	double	speed;

	mlx_mouse_get_pos(OS_MLX_REQ_PARAMS, &x, &y);
	speed = x * game->cam.mouse_sens
		- (game->map->res_x / 2 * game->cam.mouse_sens);
	rotate_cam(game, speed);
	if (x != game->map->res_x / 2)
	{
		mlx_mouse_move(OS_MLX_REQ_PARAMS,
			game->map->res_x / 2, game->map->res_y / 2);
	}
	return (1);
}

int	mousebtnpress(int btncode, int x, int y, t_game *game)
{
	x = 0;
	y = 0;
	if (btncode == BTN_SCROLL_UP)
		game->cam.mouse_sens += 0.01;
	else if (btncode == BTN_SCROLL_DOWN)
		game->cam.mouse_sens -= 0.01;
	if (game->cam.mouse_sens <= 0.00)
		game->cam.mouse_sens = 0.01;
	else if (game->cam.mouse_sens >= 0.31)
		game->cam.mouse_sens = 0.30;
	return (1);
}
