/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:04:23 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/16 20:24:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_show_hide(t_game *game, int hidden)
{
	if (hidden)
		return (mlx_mouse_hide(game->mlx->core, game->mlx->win));
	else
		return (mlx_mouse_show(game->mlx->core, game->mlx->win));
}

int	move_mouse(t_game *game, int x, int y)
{
	return (mlx_mouse_move(game->mlx->core, game->mlx->win, x, y));
}

int	win_focus(t_game *game)
{
	move_mouse(game, game->map->res_x / 2, game->map->res_y / 2);
	return (1);
}

// mlx_mouse_get_pos is used below to get the latest mouse position, as the
// parameters int x and int y are sometimes slightly behind

int	mousemove(int x, int y, t_game *game)
{
	double	speed;

	mlx_mouse_get_pos(game->mlx->core, game->mlx->win, &x, &y);
	speed = x * game->cam.mouse_sens
		- (game->map->res_x / 2 * game->cam.mouse_sens);
	rotate_cam(game, speed);
	if ((unsigned int)x != game->map->res_x / 2)
	{
		mlx_mouse_move(game->mlx->core, game->mlx->win,
			game->map->res_x / 2, game->map->res_y / 2);
	}
	return (1);
}

int	mousebtnpress(int btncode, int x, int y, t_game *game)
{
	x = x - y;
	y = x - y;
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
