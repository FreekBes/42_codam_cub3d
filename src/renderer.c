/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:01:14 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/13 21:11:04 by fbes          ########   odam.nl         */
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
	handle_key_presses(game);
	mlx_do_sync(game->mlx->core);
	render_floor_ceil(game);
	render_walls(game);
	render_sprites(game);
}

int	draw_next_frame(t_game *game)
{
	render_next_frame(game);
	return (mlx_put_image_to_window(game->mlx->core, game->mlx->win,
			game->mlx->img.img_ptr, 0, 0));
}
