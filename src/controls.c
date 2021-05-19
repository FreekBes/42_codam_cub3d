/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:03:29 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 14:39:02 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_key_presses(t_keys_status *key_status)
{
	key_status->w = 0;
	key_status->a = 0;
	key_status->s = 0;
	key_status->d = 0;
	key_status->left = 0;
	key_status->right = 0;
	key_status->shift = 0;
}

void	handle_key_presses(t_game *game)
{
	double	move_dir_fb;
	double	move_dir_side;

	move_dir_fb = 0;
	move_dir_side = 0;
	if (game->key_stat.shift)
		game->cam.speed_mod = CAM_SPRINT_SPEED_MOD;
	else
		game->cam.speed_mod = 1;
	if (game->key_stat.w)
		move_dir_fb += 1;
	if (game->key_stat.s)
		move_dir_fb -= 1;
	if (game->key_stat.d)
		move_dir_side += 1;
	if (game->key_stat.a)
		move_dir_side -= 1;
	if (move_dir_fb != 0 || move_dir_side != 0)
		move_cam(game, move_dir_fb, move_dir_side);
	if (game->key_stat.right && !game->key_stat.left)
		rotate_cam(game, 1);
	else if (game->key_stat.left && !game->key_stat.right)
		rotate_cam(game, -1);
}

int	keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game, NULL, NULL);
	else if (keycode == KEY_LEFT)
		game->key_stat.left = 1;
	else if (keycode == KEY_RIGHT)
		game->key_stat.right = 1;
	else if (keycode == KEY_W)
		game->key_stat.w = 1;
	else if (keycode == KEY_A)
		game->key_stat.a = 1;
	else if (keycode == KEY_S)
		game->key_stat.s = 1;
	else if (keycode == KEY_D)
		game->key_stat.d = 1;
	else if (keycode == KEY_LSHIFT || keycode == KEY_RSHIFT)
		game->key_stat.shift = 1;
	return (1);
}

int	keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT)
		game->key_stat.left = 0;
	else if (keycode == KEY_RIGHT)
		game->key_stat.right = 0;
	else if (keycode == KEY_W)
		game->key_stat.w = 0;
	else if (keycode == KEY_A)
		game->key_stat.a = 0;
	else if (keycode == KEY_S)
		game->key_stat.s = 0;
	else if (keycode == KEY_D)
		game->key_stat.d = 0;
	else if (keycode == KEY_LSHIFT || keycode == KEY_RSHIFT)
		game->key_stat.shift = 0;
	return (1);
}
