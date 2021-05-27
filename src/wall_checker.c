/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 10:20:18 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

// modified from
// https://www.geeksforgeeks.org/boundary-fill-algorithm/
// below method fills all spaces that aren't walls with * characters.
// if the map at position x, y is considered "outside" of the level,
// 1 is returned, stating that the map is invalid, since we can reach
// places outside of the walls.

int	b_fill(t_game *game, char **lvl, int x, int y)
{
	if (outside(game, lvl, x, y))
		return (1);
	if (lvl[x][y] != '1' && lvl[x][y] != '*')
	{
		lvl[x][y] = '*';
		if (b_fill(game, lvl, x + 1, y))
			return (1);
		if (b_fill(game, lvl, x, y + 1))
			return (1);
		if (b_fill(game, lvl, x - 1, y))
			return (1);
		if (b_fill(game, lvl, x, y - 1))
			return (1);
		if (b_fill(game, lvl, x - 1, y - 1))
			return (1);
		if (b_fill(game, lvl, x - 1, y + 1))
			return (1);
		if (b_fill(game, lvl, x + 1, y - 1))
			return (1);
		if (b_fill(game, lvl, x + 1, y + 1))
			return (1);
	}
	return (0);
}

int	map_surrounded_by_walls(t_game *game)
{
	char		**temp_lvl;

	temp_lvl = lvl_copy(game->map);
	if (!temp_lvl)
		return (-1);
	if (b_fill(game, temp_lvl, game->cam.pos_x, game->cam.pos_y))
	{
		ft_free(temp_lvl);
		return (0);
	}
	ft_free(temp_lvl);
	return (1);
}
