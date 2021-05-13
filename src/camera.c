/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 19:58:04 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/13 20:27:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// COLLISION CHECK STAGES
// stage 1: forward/backward x check
// stage 2: forward/backward y check
// stage 3: left/right x check
// stage 4: left/right y check
// does not check for object collision, only walls

static int	collision_check(t_game *game, double dir, int stage)
{
	int		x;
	int		y;

	if (stage < 1 || stage > 4)
		return (0);
	if (stage == 2 || stage == 4)
		x = (int)(game->cam.pos_x);
	else if (stage == 1 || stage == 3)
		y = (int)(game->cam.pos_y);
	if (stage == 1)
		x = (int)(game->cam.pos_x + game->cam.dir_x * dir);
	else if (stage == 2)
		y = (int)(game->cam.pos_y + game->cam.dir_y * dir);
	else if (stage == 3)
		x = (int)(game->cam.pos_x + game->cam.plane_x * dir);
	else if (stage == 4)
		y = (int)(game->cam.pos_y + game->cam.plane_y * dir);
	return (game->map->lvl[x][y] != '1');
}

void	rotate_cam(t_game *game, double dir)
{
	double		rot_speed;
	double		old_dir_x;
	double		old_plane_x;

	rot_speed = dir * CAM_ROT_SPEED;
	old_dir_x = game->cam.dir_x;
	game->cam.dir_x = game->cam.dir_x * cos(-rot_speed)
		- game->cam.dir_y * sin(-rot_speed);
	game->cam.dir_y = old_dir_x * sin(-rot_speed)
		+ game->cam.dir_y * cos(-rot_speed);
	old_plane_x = game->cam.plane_x;
	game->cam.plane_x = game->cam.plane_x * cos(-rot_speed)
		- game->cam.plane_y * sin(-rot_speed);
	game->cam.plane_y = old_plane_x * sin(-rot_speed)
		+ game->cam.plane_y * cos(-rot_speed);
}

void	move_cam(t_game *game, double dir_fb, double dir_side)
{
	double	move_speed_fb;
	double	move_speed_side;

	move_speed_fb = dir_fb * CAM_MOV_SPEED_FORW_BACKW * game->cam.speed_mod;
	move_speed_side = dir_side * CAM_MOV_SPEED_SIDEWAYS * game->cam.speed_mod;
	if (collision_check(game, move_speed_fb, 1))
		game->cam.pos_x += game->cam.dir_x * move_speed_fb;
	if (collision_check(game, move_speed_fb, 2))
		game->cam.pos_y += game->cam.dir_y * move_speed_fb;
	if (collision_check(game, move_speed_side, 3))
		game->cam.pos_x += game->cam.plane_x * move_speed_side;
	if (collision_check(game, move_speed_side, 4))
		game->cam.pos_y += game->cam.plane_y * move_speed_side;
}
