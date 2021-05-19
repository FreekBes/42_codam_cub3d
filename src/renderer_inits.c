/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_inits.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 21:08:01 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 12:33:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// for all methods below, see https://lodev.org/cgtutor/raycasting.html
// for a thorough explanation on how all of this works.

static void	setup_step_side_dist(t_game *game, t_render_holder_walls *hold)
{
	if (hold->ray_dir.x < 0)
	{
		hold->step.x = -1;
		hold->side_dist.x = (game->cam.pos_x - hold->map.x)
			* hold->delta_dist.x;
	}
	else
	{
		hold->step.x = 1;
		hold->side_dist.x = (hold->map.x + 1.0 - game->cam.pos_x)
			* hold->delta_dist.x;
	}
	if (hold->ray_dir.y < 0)
	{
		hold->step.y = -1;
		hold->side_dist.y = (game->cam.pos_y - hold->map.y)
			* hold->delta_dist.y;
	}
	else
	{
		hold->step.y = 1;
		hold->side_dist.y = (hold->map.y + 1.0 - game->cam.pos_y)
			* hold->delta_dist.y;
	}
}

void	init_ray(t_game *game, t_render_holder_walls *hold)
{
	hold->cam_x = 2 * hold->pixel.x / (double)(game->map->res_x) - 1;
	hold->ray_dir.x = game->cam.dir_x + game->cam.plane_x * hold->cam_x;
	hold->ray_dir.y = game->cam.dir_y + game->cam.plane_y * hold->cam_x;
	hold->map.x = (int)(game->cam.pos_x);
	hold->map.y = (int)(game->cam.pos_y);
	hold->delta_dist.x = fabs(1 / hold->ray_dir.x);
	hold->delta_dist.y = fabs(1 / hold->ray_dir.y);
	setup_step_side_dist(game, hold);
}

void	init_drawer(t_game *game, t_render_holder_walls *hold)
{
	if (hold->side == 0)
	{
		hold->perp_wall_dist = (hold->map.x - game->cam.pos_x
				+ (1 - hold->step.x) / 2) / hold->ray_dir.x;
	}
	else
	{
		hold->perp_wall_dist = (hold->map.y - game->cam.pos_y
				+ (1 - hold->step.y) / 2) / hold->ray_dir.y;
	}
	hold->line_height = (int)(game->map->res_y / hold->perp_wall_dist);
	hold->draw_start = -hold->line_height / 2 + game->map->res_y / 2;
	if (hold->draw_start < 0)
		hold->draw_start = 0;
	hold->draw_end = hold->line_height / 2 + game->map->res_y / 2;
	if (hold->draw_end >= (int)(game->map->res_y))
		hold->draw_end = game->map->res_y - 1;
	if (hold->side == 0)
		hold->wall_x = game->cam.pos_y + hold->perp_wall_dist * hold->ray_dir.y;
	else
		hold->wall_x = game->cam.pos_x + hold->perp_wall_dist * hold->ray_dir.x;
}

void	init_texture_draw(t_game *game, t_render_holder_walls *hold)
{
	hold->wall_x -= floor((hold->wall_x));
	if (hold->side == 0 && hold->ray_dir.x > 0)
		hold->tex = game->map->tex_so;
	else if (hold->side == 0 && hold->ray_dir.x <= 0)
		hold->tex = game->map->tex_no;
	else if (hold->side == 1 && hold->ray_dir.y > 0)
		hold->tex = game->map->tex_ea;
	else if (hold->side == 1 && hold->ray_dir.y <= 0)
		hold->tex = game->map->tex_we;
	hold->tex_c.x = (int)(hold->wall_x * (double)(hold->tex->w));
	hold->tex_c.x = hold->tex->w - hold->tex_c.x - 1;
	hold->tex_step = 1.0 * hold->tex->h / hold->line_height;
	hold->tex_pos = (hold->draw_start - game->map->res_y
			/ 2 + hold->line_height / 2) * hold->tex_step;
}

// see https://lodev.org/cgtutor/raycasting3.html
// for an explanation of the method below.

void	init_sprite_render(t_game *game, t_render_holder_sprites *hold)
{
	hold->sprite_pos.x = hold->sprite->x - game->cam.pos_x;
	hold->sprite_pos.y = hold->sprite->y - game->cam.pos_y;
	hold->inv_det = 1.0 / (game->cam.plane_x * game->cam.dir_y
			- game->cam.dir_x * game->cam.plane_y);
	hold->transform.x = hold->inv_det * (game->cam.dir_y * hold->sprite_pos.x
			- game->cam.dir_x * hold->sprite_pos.y);
	hold->transform.y = hold->inv_det * (-game->cam.plane_y
			* hold->sprite_pos.x + game->cam.plane_x * hold->sprite_pos.y);
	hold->sprite_screen_x = (1 + hold->transform.x / hold->transform.y)
		* (int)(game->map->res_x / 2);
	hold->sprite_dims.h = abs((int)(game->map->res_y / hold->transform.y));
	hold->draw_start.y = -hold->sprite_dims.h / 2 + game->map->res_y / 2;
	if (hold->draw_start.y < 0)
		hold->draw_start.y = 0;
	hold->draw_end.y = hold->sprite_dims.h / 2 + game->map->res_y / 2;
	if (hold->draw_end.y >= (int)(game->map->res_y))
		hold->draw_end.y = game->map->res_y - 1;
	hold->sprite_dims.w = abs((int)(game->map->res_y / hold->transform.y));
	hold->draw_start.x = -hold->sprite_dims.w / 2 + hold->sprite_screen_x;
	if (hold->draw_start.x < 0)
		hold->draw_start.x = 0;
	hold->draw_end.x = hold->sprite_dims.w / 2 + hold->sprite_screen_x;
	if (hold->draw_end.x >= (int)(game->map->res_x))
		hold->draw_end.x = game->map->res_x - 1;
	hold->stripe = hold->draw_start.x;
}
