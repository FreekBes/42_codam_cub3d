/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:01:14 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/13 20:11:07 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	render_floor_ceil(t_game *game)
{
	t_rect	ceil_rect;
	t_rect	floor_rect;

	ceil_rect.x = 0;
	ceil_rect.y = 0;
	ceil_rect.w = game->map->res_x;
	ceil_rect.h = game->map->res_y * 0.5;
	ceil_rect.c = game->map->col_ceiling;
	put_rect(&game->mlx->img, &ceil_rect);
	floor_rect.x = 0;
	floor_rect.y = game->map->res_y * 0.5;
	floor_rect.w = game->map->res_x;
	floor_rect.h = floor_rect.y;
	floor_rect.c = game->map->col_floor;
	put_rect(&game->mlx->img, &floor_rect);
}

void	render_next_frame(t_game *game)
{
	int				x;
	int				y;
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
	double			wall_x;
	t_tex			*tex;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;

	handle_key_presses(game);
	mlx_do_sync(game->mlx->core);
	render_floor_ceil(game);
	x = 0;
	while (x < (int)(game->map->res_x))
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
		if (draw_end >= (int)(game->map->res_y))
			draw_end = game->map->res_y - 1;
		if (side == 0)
			wall_x = game->cam.pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = game->cam.pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor((wall_x));
		if (side == 0 && ray_dir_x > 0)		// S
			tex = game->map->tex_so;
		else if (side == 0 && ray_dir_x <= 0) // N
			tex = game->map->tex_no;
		else if (side == 1 && ray_dir_y > 0) // E
			tex = game->map->tex_ea;
		else if (side == 1 && ray_dir_y <= 0) // W
			tex = game->map->tex_we;
		tex_x = (int)(wall_x * (double)(tex->w));
		tex_x = tex->w - tex_x - 1;
		step = 1.0 * tex->h / line_height;
		tex_pos = (draw_start - game->map->res_y / 2 + line_height / 2) * step;
		y = draw_start;
		while (y < draw_end)
		{
			tex_y = (int)tex_pos & (tex->h - 1);
			tex_pos += step;
			color = get_color(tex, tex_x, tex_y);
			if (side == 1 && ray_dir_y > 0)
				color = brighten(color);
			else if (side == 1 && ray_dir_y <= 0)
				color = darken(color);
			put_pixel(&game->mlx->img, x, y, color);
			y++;
		}
		game->cam.z_buffer[x] = perp_wall_dist;
		x++;
	}
	render_sprites(game);
}

int	draw_next_frame(t_game *game)
{
	render_next_frame(game);
	return (mlx_put_image_to_window(game->mlx->core, game->mlx->win,
		game->mlx->img.img_ptr, 0, 0));
}
