/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:03:29 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "MLX42/MLX42.h"

void	handle_key_presses(t_game *game)
{
	double	move_dir_fb;
	double	move_dir_side;
	bool	right;
	bool	left;

	move_dir_fb = 0;
	move_dir_side = 0;
	right = mlx_is_key_down(game->mlx->core, MLX_KEY_RIGHT);
	left = mlx_is_key_down(game->mlx->core, MLX_KEY_LEFT);
	if (mlx_is_key_down(game->mlx->core, MLX_KEY_LEFT_SHIFT))
		game->cam.speed_mod = CAM_SPRINT_SPEED_MOD;
	else
		game->cam.speed_mod = 1;
	if (mlx_is_key_down(game->mlx->core, MLX_KEY_W))
		move_dir_fb += 1;
	if (mlx_is_key_down(game->mlx->core, MLX_KEY_S))
		move_dir_fb -= 1;
	if (mlx_is_key_down(game->mlx->core, MLX_KEY_D))
		move_dir_side += 1;
	if (mlx_is_key_down(game->mlx->core, MLX_KEY_A))
		move_dir_side -= 1;
	if (move_dir_fb != 0 || move_dir_side != 0)
		move_cam(game, move_dir_fb, move_dir_side);
	if (right && !left)
		rotate_cam(game, 1);
	else if (left && !right)
		rotate_cam(game, -1);
}
