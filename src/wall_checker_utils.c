/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_checker_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 22:15:56 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 10:38:33 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_map_node	*new_map_node(int x, int y, char c)
{
	t_map_node	*helper;

	helper = (t_map_node *)malloc(sizeof(t_map_node));
	if (helper)
	{
		helper->x = x;
		helper->y = y;
		helper->c = c;
	}
	return (helper);
}

int	clear_queue(t_list *queue, char **temp_lvl, size_t lvl_h)
{
	if (temp_lvl)
		free_lvl(temp_lvl, lvl_h);
	ft_lstclear(&queue, &item_free_simple);
	return (0);
}

// while a space is technically not inside, for the algorithm in this file
// it needs to be checked for (or maps like maps/invalid.cub are marked valid)

int	inside(char **temp_lvl, int x, int y)
{
	return (ft_strchr(" 02NSEW", temp_lvl[x][y]) != NULL);
}

// outside check: if
// - x or y is outside of map boundaries,
// - the current character is a space or EOL
// - the current character is "inside" on y axis 0,
// return (1): the current position would be outside of the map.

int	outside(t_game *game, char **temp_lvl, int x, int y)
{
	if (x == -1 || y == -1)
		return (1);
	if (x == game->map->lvl_h || y == game->map->lvl_w)
		return (1);
	if (temp_lvl[x][y] == ' ' || temp_lvl[x][y] == '\0')
		return (1);
	if (y == 0 && inside(temp_lvl, x, y))
		return (1);
	return (0);
}

