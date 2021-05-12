/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 16:35:38 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/12 22:16:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// EXPLANATION OF WHAT THIS FILE DOES
// check if map is surrounded by walls by using a flood fill algorithm
// on the starting position. if it is possible to reach outside of the
// map, the map is not surrounded by walls.
// check wikipedia article on span (flood) filling for explanation.
// https://en.wikipedia.org/wiki/Flood_fill
// x axis map: top to bottom
// y axis map: left to right

static void	scan(t_list **queue, char **temp_lvl, t_coords *l, t_coords *r)
{
	int		added;
	int		x;

	if (l && r)
	{
		added = 0;
		x = l->x;
		while (x <= r->x)
		{
			if (!inside(temp_lvl, x, l->y))
				added = 0;
			else if (added == 0)
			{
				ft_lstadd_back(queue,
					ft_lstnew(new_map_node(x, l->y, temp_lvl[x][l->y])));
				added = 1;
			}
			x++;
		}
	}
	if (l)
		ft_free(l);
	if (r)
		ft_free(r);
}

static int	check_row(t_game *game, char **temp_lvl, t_coords *c, int *lx)
{
	*lx = c->x;
	while (inside(temp_lvl, *lx - 1, c->y))
	{
		temp_lvl[*lx - 1][c->y] = '*';
		*lx = *lx - 1;
		if (outside(game, temp_lvl, *lx - 1, c->y))
			return (0);
	}
	while (inside(temp_lvl, c->x, c->y))
	{
		temp_lvl[c->x][c->y] = '*';
		c->x++;
		if (outside(game, temp_lvl, c->x, c->y))
			return (0);
	}
	return (1);
}

static int	handle_queue(t_game *game, t_list **queue, char **temp_lvl)
{
	t_list		*current;
	int			lx;
	t_coords	c;

	current = *queue;
	if (!(current->content))
		return (clear_queue(*queue, temp_lvl, game->map->lvl_h));
	c.x = ((t_map_node *)current->content)->x;
	c.y = ((t_map_node *)current->content)->y;
	if (outside(game, temp_lvl, c.x, c.y))
		return (clear_queue(*queue, temp_lvl, game->map->lvl_h));
	if (check_row(game, temp_lvl, &c, &lx) == 0)
		return (clear_queue(*queue, temp_lvl, game->map->lvl_h));
	*queue = (*queue)->next;
	ft_lstdelone(current, &item_free_simple);
	scan(queue, temp_lvl,
		new_coords(lx, c.y + 1), new_coords(c.x - 1, c.y + 1));
	scan(queue, temp_lvl,
		new_coords(lx, c.y - 1), new_coords(c.x - 1, c.y - 1));
	return (1);
}

int	map_surrounded_by_walls(t_game *game)
{
	char		**temp_lvl;
	t_coords	c;
	t_list		*queue;

	temp_lvl = lvl_copy(game->map);
	if (!temp_lvl)
		return (0);
	c.x = game->cam.pos_x;
	c.y = game->cam.pos_y;
	queue = ft_lstnew(new_map_node(c.x, c.y, temp_lvl[c.x][c.y]));
	if (!queue)
		return (free_lvl(temp_lvl, game->map->lvl_h));
	while (queue)
	{
		if (handle_queue(game, &queue, temp_lvl) == 0)
			return (0);
	}
	free_lvl(temp_lvl, game->map->lvl_h);
	return (1);
}
