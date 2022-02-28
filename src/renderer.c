/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 20:01:14 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/28 20:38:37 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "MLX42/MLX42.h"

// render the floor and the ceiling, basically just two rectangles
// each the size of half the window.

static void	render_floor_ceil(t_game *game)
{
	t_rect	ceil_rect;
	t_rect	floor_rect;

	ceil_rect.x = 0;
	ceil_rect.y = 0;
	ceil_rect.w = game->map->res_x;
	ceil_rect.h = game->map->res_y >> 1;
	ceil_rect.c = game->map->col_ceiling;
	put_rect(game->mlx, &ceil_rect);
	floor_rect.x = 0;
	floor_rect.y = game->map->res_y >> 1;
	floor_rect.w = game->map->res_x;
	floor_rect.h = floor_rect.y;
	floor_rect.c = game->map->col_floor;
	put_rect(game->mlx, &floor_rect);
}

// render the next frame. An overview of the steps:
// - first check for keys being pressed on the keyboard
//   and move the camera as such (all in one function)
// - then sync the mlx core, which is neccessary to avoid flickering
// - render the floor and the ceiling
// - overwrite the floor and the ceiling with walls were neccessary
// - overwrite the floor, ceiling and walls with sprites were neccessary

void	render_next_frame(t_game *game)
{
	handle_key_presses(game);
	// check_mouse_movement(game);
	render_floor_ceil(game);
	render_walls(game);
	render_sprites(game);
}

// below function renders the next frame and outputs it to the window.
// these functions are separated in order to support the BMP export
// functionality without opening an MLX window.

void	draw_next_frame(void *game)
{
	render_next_frame((t_game *)game);
}
