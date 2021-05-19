/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_walls.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 19:57:36 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 12:39:49 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// see https://lodev.org/cgtutor/raycasting.html and renderer_inits.c
// for an explanation of all methods below.

static void	raycast(t_game *game, t_render_holder_walls *hold)
{
	hold->hit = 0;
	while (hold->hit == 0)
	{
		if (hold->side_dist.x < hold->side_dist.y)
		{
			hold->side_dist.x += hold->delta_dist.x;
			hold->map.x += hold->step.x;
			hold->side = 0;
		}
		else
		{
			hold->side_dist.y += hold->delta_dist.y;
			hold->map.y += hold->step.y;
			hold->side = 1;
		}
		if (game->map->lvl[hold->map.x][hold->map.y] == '1')
			hold->hit = 1;
	}
}

static void	draw_wall_y(t_game *game, t_render_holder_walls *hold)
{
	hold->pixel.y = hold->draw_start;
	while (hold->pixel.y < hold->draw_end)
	{
		hold->tex_c.y = (int)hold->tex_pos & (hold->tex->h - 1);
		hold->tex_pos += hold->tex_step;
		hold->color = get_color(hold->tex, hold->tex_c.x, hold->tex_c.y);
		if (hold->side == 1 && hold->ray_dir.y > 0)
			hold->color = brighten(hold->color);
		else if (hold->side == 1 && hold->ray_dir.y <= 0)
			hold->color = darken(hold->color);
		put_pixel(&game->mlx->img, hold->pixel.x, hold->pixel.y, hold->color);
		hold->pixel.y++;
	}
}

void	render_walls(t_game *game)
{
	static t_render_holder_walls	hold;

	hold.pixel.x = 0;
	while (hold.pixel.x < (int)(game->map->res_x))
	{
		init_ray(game, &hold);
		raycast(game, &hold);
		init_drawer(game, &hold);
		init_texture_draw(game, &hold);
		draw_wall_y(game, &hold);
		game->cam.z_buffer[hold.pixel.x] = hold.perp_wall_dist;
		hold.pixel.x++;
	}
}
