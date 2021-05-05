/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 16:35:38 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/05 20:02:27 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map_node	*new_map_node(int x, int y, char c)
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

static void	delete_queue_item(void *item)
{
	if (item)
		free(item);
}

static int	clear_queue(t_list *queue, char **temp_lvl, size_t lvl_h)
{
	if (temp_lvl)
		free_lvl(temp_lvl, lvl_h);
	ft_lstclear(&queue, &delete_queue_item);
	return (0);
}

static int	inside(char **temp_lvl, int x, int y)
{
	return (ft_strchr("02NSEW", temp_lvl[x][y]) != NULL);
}

static int	outside(t_game *game, char **temp_lvl, int x, int y)
{
	if (x == -1 || y == -1 || x == game->map->lvl_h || y == game->map->lvl_w - 1
		|| temp_lvl[x][y + 1] == '\0' || temp_lvl[x][y + 1] == ' '
		|| (y == 0 && inside(temp_lvl, x, y))
		|| temp_lvl[x][y - 1] == '\0' || temp_lvl[x][y - 1] == ' ')
		return (1);
	return (0);
}

static void	scan(t_list **queue, char **temp_lvl, int lx, int rx, int y)
{
	int		added;
	int		x;

	added = 0;
	x = lx;
	while (x <= rx)
	{
		if (!inside(temp_lvl, x, y))
			added = 0;
		else if (added == 0)
		{
			ft_lstadd_back(queue,
				ft_lstnew(new_map_node(x, y, temp_lvl[x][y])));
			added = 1;
		}
		x++;
	}
}

// x axis: top to bottom
// y axis: left to right

int	map_surrounded_by_walls(t_game *game)
{
	char		**temp_lvl;
	int			x;
	int			y;
	int			lx;
	t_list		*queue;
	t_list		*current;

	temp_lvl = lvl_copy(game->map);
	if (!temp_lvl)
		return (0);
	x = game->cam.pos_x;
	y = game->cam.pos_y;
	queue = ft_lstnew(new_map_node(x, y, temp_lvl[x][y]));
	if (!queue)
		return (free_lvl(temp_lvl, game->map->lvl_h));
	while (queue)
	{
		current = queue;
		if (!(current->content))
			return (clear_queue(queue, temp_lvl, game->map->lvl_h));
		x = ((t_map_node *)current->content)->x;
		y = ((t_map_node *)current->content)->y;
		if (outside(game, temp_lvl, x, y))
			return (clear_queue(queue, temp_lvl, game->map->lvl_h));
		lx = x;
		while (inside(temp_lvl, lx - 1, y))
		{
			temp_lvl[lx - 1][y] = '*';
			lx--;
			if (outside(game, temp_lvl, lx - 1, y))
				return (clear_queue(queue, temp_lvl, game->map->lvl_h));
		}
		while (inside(temp_lvl, x, y))
		{
			temp_lvl[x][y] = '*';
			x++;
			if (outside(game, temp_lvl, x, y))
				return (clear_queue(queue, temp_lvl, game->map->lvl_h));
		}
		queue = queue->next;
		ft_lstdelone(current, &delete_queue_item);
		scan(&queue, temp_lvl, lx, x - 1, y + 1);
		scan(&queue, temp_lvl, lx, x - 1, y - 1);
	}
	free_lvl(temp_lvl, game->map->lvl_h);
	return (1);
}
