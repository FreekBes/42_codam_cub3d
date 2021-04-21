/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/21 19:45:35 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	size_t	i;

	if (map->tex_no)
		free(map->tex_no);
	if (map->tex_so)
		free(map->tex_so);
	if (map->tex_we)
		free(map->tex_we);
	if (map->tex_ea)
		free(map->tex_ea);
	if (map->tex_sprite)
		free(map->tex_sprite);
	if (map->lvl)
	{
		i = 0;
		while (i < map->lvl_h)
		{
			if (map->lvl[i])
				free(map->lvl[i]);
			i++;
		}
		free(map->lvl);
	}
	free(map);
}

static int	exit_game(t_game game, char *error_msg)
{
	mlx_mouse_show(OS_MLX_REQ_PARAMS_MOUSE_SHOW_HIDE);
	if (error_msg)
		print_error(error_msg);
	free_mlx_context(game.mlx);
	free_map(game.map);
	//system("leaks cub3D");
	exit(0);
	return (0);
}

static int	exit_hook(t_game *game)
{
	return (exit_game(*game, NULL));
}

static void	render_floor_ceil(t_game *game)
{
	t_rect	ceil_rect;
	t_rect	floor_rect;

	ceil_rect.x = 0;
	ceil_rect.y = 0;
	ceil_rect.w = game->map->res_x;
	ceil_rect.h = game->map->res_y * 0.5;
	ceil_rect.c = game->map->col_ceiling;
	put_rect(game->mlx->img, &ceil_rect);
	floor_rect.x = 0;
	floor_rect.y = game->map->res_y * 0.5;
	floor_rect.w = game->map->res_x;
	floor_rect.h = floor_rect.y;
	floor_rect.c = game->map->col_floor;
	put_rect(game->mlx->img, &floor_rect);
}

static int	set_starting_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->lvl_h)
	{
		j = 0;
		while (j < game->map->lvl_w && game->map->lvl[i][j] != '\0')
		{
			if (ft_strchr("NSEW", game->map->lvl[i][j]))
			{
				game->cam.pos_x = i + 0.5;
				game->cam.pos_y = j + 0.5;
				if (game->map->lvl[i][j] == 'N' || game->map->lvl[i][j] == 'S')
				{
					game->cam.dir_y = 0;
					game->cam.plane_x = 0;
				}
				else
				{
					game->cam.dir_x = 0;
					game->cam.plane_y = 0;
				}
				if (game->map->lvl[i][j] == 'N')
				{
					game->cam.dir_x = -1;
					game->cam.plane_y = 0.66;
				}
				else if (game->map->lvl[i][j] == 'S')
				{
					game->cam.dir_x = 1;
					game->cam.plane_y = -0.66;
				}
				else if (game->map->lvl[i][j] == 'W')
				{
					game->cam.dir_y = -1;
					game->cam.plane_x = -0.66;
				}
				else
				{
					game->cam.dir_y = 1;
					game->cam.plane_x = 0.66;
				}
				return (1);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

static void	rotate_cam(t_game *game, double dir)
{
	double		rot_speed;
	double		old_dir_x;
	double		old_plane_x;

	rot_speed = dir * CAM_ROT_SPEED;
	old_dir_x = game->cam.dir_x;
	game->cam.dir_x = game->cam.dir_x * cos(-rot_speed) - game->cam.dir_y * sin(-rot_speed);
	game->cam.dir_y = old_dir_x * sin(-rot_speed) + game->cam.dir_y * cos(-rot_speed);
	old_plane_x = game->cam.plane_x;
	game->cam.plane_x = game->cam.plane_x * cos(-rot_speed) - game->cam.plane_y * sin(-rot_speed);
	game->cam.plane_y = old_plane_x * sin(-rot_speed) + game->cam.plane_y * cos(-rot_speed);
}

static void	move_cam(t_game *game, double dir_fb, double dir_side)
{
	double	move_speed_fb;
	double	move_speed_side;

	move_speed_fb = dir_fb * CAM_MOV_SPEED_FORW_BACKW * game->cam.speed_mod;
	move_speed_side = dir_side * CAM_MOV_SPEED_SIDEWAYS * game->cam.speed_mod;
	if (game->map->lvl[(int)(game->cam.pos_x + game->cam.dir_x * move_speed_fb)][(int)(game->cam.pos_y)] != '1')
		game->cam.pos_x += game->cam.dir_x * move_speed_fb;
	if (game->map->lvl[(int)(game->cam.pos_x)][(int)(game->cam.pos_y + game->cam.dir_y * move_speed_fb)] != '1')
		game->cam.pos_y += game->cam.dir_y * move_speed_fb;
}

static void	handle_key_presses(t_game *game)
{
	if (game->key_stat.shift)
		game->cam.speed_mod = CAM_SPRINT_SPEED_MOD;
	else
		game->cam.speed_mod = 1;
	if (game->key_stat.w && !game->key_stat.s)
		move_cam(game, 1, 0);
	else if (game->key_stat.s && !game->key_stat.w)
		move_cam(game, -1, 0);
	if (game->key_stat.right && !game->key_stat.left)
		rotate_cam(game, 1);
	else if (game->key_stat.left && !game->key_stat.right)
		rotate_cam(game, -1);
}

static int	render_next_frame(t_game *game)
{
	int				x;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	unsigned int	color;

	handle_key_presses(game);
	render_floor_ceil(game);
	x = 0;
	while (x < game->map->res_x)
	{
		camera_x = 2 * x / (double)(game->map->res_x) - 1;
		ray_dir_x = game->cam.dir_x + game->cam.plane_x * camera_x;
		ray_dir_y = game->cam.dir_y + game->cam.plane_y * camera_x;
		map_x = (int)(game->cam.pos_x);
		map_y = (int)(game->cam.pos_y);
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->cam.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->cam.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->cam.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->cam.pos_y) * delta_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map->lvl[map_x][map_y] == '1')
				hit = 1;
		}
		//printf("hit (%d) at: %d, %d (%c)\n", hit, map_x, map_y, game->map->lvl[map_x][map_y]);
		if (side == 0)
			perp_wall_dist = (map_x - game->cam.pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->cam.pos_y + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(game->map->res_y / perp_wall_dist);

		draw_start = -line_height / 2 + game->map->res_y / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + game->map->res_y / 2;
		if (draw_end >= game->map->res_y)
			draw_end = game->map->res_y - 1;
		color = 0x00FF0000;
		if (side == 1)
			color = 0x00CC0000;
		put_vert_line(game->mlx->img, x, draw_start, draw_end, color);
		x++;
	}
	return (mlx_put_image_to_window(game->mlx->core, game->mlx->win,
		game->mlx->img->img_ptr, 0, 0));
}

static int	keypress(int keycode, t_game *game)
{
	//printf("keypress! %d\n", keycode);
	if (keycode == KEY_ESC)
		exit_game(*game, NULL);
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
	printf("dirX: %f, dirY: %f, planeX: %f, planeY: %f\n", game->cam.dir_x, game->cam.dir_y, game->cam.plane_x, game->cam.plane_y);
	return (1);
}

static int	keyrelease(int keycode, t_game *game)
{
	//printf("keyrelease! %d\n", keycode);
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

// mlx_mouse_get_pos is used below to get the latest mouse position, as the
// parameters int x and int y are sometimes slightly behind

static int	mousemove(int x, int y, t_game *game)
{
	double	speed;

	mlx_mouse_get_pos(OS_MLX_REQ_PARAMS, &x, &y);
	speed = x * CAM_MOUSE_SENSITIVITY - (game->map->res_x / 2 * CAM_MOUSE_SENSITIVITY);
	rotate_cam(game, speed);
	if (x != game->map->res_x / 2)
		mlx_mouse_move(OS_MLX_REQ_PARAMS, game->map->res_x / 2, game->map->res_y / 2);
	return (1);
}

static void	init_game_win(t_game *game)
{
	mlx_mouse_hide(OS_MLX_REQ_PARAMS_MOUSE_SHOW_HIDE);
	mlx_mouse_move(OS_MLX_REQ_PARAMS, game->map->res_x / 2, game->map->res_y / 2);
	mlx_hook(game->mlx->win, 17, 1L<<17, &exit_hook, game);
	mlx_hook(game->mlx->win, 2, 1L<<0, &keypress, game);
	mlx_hook(game->mlx->win, 3, 1L<<1, &keyrelease, game);
	mlx_hook(game->mlx->win, 6, 1L<<6, &mousemove, game);
	mlx_loop_hook(game->mlx->core, render_next_frame, game);
}

int	main(int argc, char **argv)
{
	t_game		game;
	int			x;
	int			y;

	if (argc < 2)
		return (print_error("No map specified as first argument"));
	game.cam.speed_mod = 1;
	game.map = parse_map(argv[1]);
	if (set_starting_pos(&game) < 0)
		return (print_error("Start position in map is not set"));
	printf("start pos: %f, %f\n", game.cam.pos_x, game.cam.pos_y);
	if (!game.map)
		return (print_error("Failed to parse map"));
	print_map(*(game.map));
	game.mlx = get_mlx_context(game.map, argv[0]);
	if (!game.mlx)
		exit_game(game, "Failed to open MLX window");
	init_game_win(&game);
	mlx_loop(game.mlx->core);
	return (exit_game(game, NULL));
}
