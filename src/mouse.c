/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:04:23 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 17:39:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "MLX42/MLX42.h"

int	win_focus(t_game *game)
{
	mlx_set_mouse_pos(game->mlx->core,
		game->map->res_x >> 1, game->map->res_y >> 1);
	return (1);
}

void	check_mouse_movement(t_game *game)
{
	double	speed;
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(game->mlx->core, &x, &y);
	speed = x * game->cam.mouse_sens
		- ((game->map->res_x >> 1) * game->cam.mouse_sens);
	rotate_cam(game, speed);
	if (x != game->map->res_x >> 1)
	{
		mlx_set_mouse_pos(game->mlx->core,
			game->map->res_x >> 1, game->map->res_y >> 1);
	}
}

void	mousescrollwheel(double xdelta, double ydelta, void *game)
{
	xdelta = 0;
	if (ydelta > 0)
		((t_game *)game)->cam.mouse_sens += 0.01;
	else if (ydelta < 0)
		((t_game *)game)->cam.mouse_sens -= 0.01;
	if (((t_game *)game)->cam.mouse_sens <= 0.00)
		((t_game *)game)->cam.mouse_sens = 0.01;
	else if (((t_game *)game)->cam.mouse_sens >= 0.31)
		((t_game *)game)->cam.mouse_sens = 0.30;
}
