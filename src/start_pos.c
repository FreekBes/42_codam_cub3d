/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_pos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:47:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/17 18:09:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_start_pos_n(t_game *game, int x, int y)
{
	if (x == 0 || y == 0
		|| x == game->map->lvl_h - 1 || y == game->map->lvl_w - 1)
		return (-1);
	game->cam.pos_x = x + 0.5;
	game->cam.pos_y = y + 0.5;
	game->cam.dir_x = -1;
	game->cam.dir_y = 0;
	game->cam.plane_x = 0;
	game->cam.plane_y = 0.66;
	return (1);
}

static int	set_start_pos_e(t_game *game, int x, int y)
{
	if (x == 0 || y == 0
		|| x == game->map->lvl_h - 1 || y == game->map->lvl_w - 1)
		return (-1);
	game->cam.pos_x = x + 0.5;
	game->cam.pos_y = y + 0.5;
	game->cam.dir_x = 0;
	game->cam.dir_y = 1;
	game->cam.plane_x = 0.66;
	game->cam.plane_y = 0;
	return (1);
}

static int	set_start_pos_s(t_game *game, int x, int y)
{
	if (x == 0 || y == 0
		|| x == game->map->lvl_h - 1 || y == game->map->lvl_w - 1)
		return (-1);
	game->cam.pos_x = x + 0.5;
	game->cam.pos_y = y + 0.5;
	game->cam.dir_x = 1;
	game->cam.dir_y = 0;
	game->cam.plane_x = 0;
	game->cam.plane_y = -0.66;
	return (1);
}

static int	set_start_pos_w(t_game *game, int x, int y)
{
	if (x == 0 || y == 0
		|| x == game->map->lvl_h - 1 || y == game->map->lvl_w - 1)
		return (-1);
	game->cam.pos_x = x + 0.5;
	game->cam.pos_y = y + 0.5;
	game->cam.dir_x = 0;
	game->cam.dir_y = -1;
	game->cam.plane_x = -0.66;
	game->cam.plane_y = 0;
	return (1);
}

int	set_starting_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->lvl_h)
	{
		j = 0;
		while (j < game->map->lvl_w && game->map->lvl[i][j] != '\0')
		{
			if (game->map->lvl[i][j] == 'N')
				return (set_start_pos_n(game, i, j));
			else if (game->map->lvl[i][j] == 'E')
				return (set_start_pos_e(game, i, j));
			else if (game->map->lvl[i][j] == 'S')
				return (set_start_pos_s(game, i, j));
			else if (game->map->lvl[i][j] == 'W')
				return (set_start_pos_w(game, i, j));
			j++;
		}
		i++;
	}
	return (-1);
}
