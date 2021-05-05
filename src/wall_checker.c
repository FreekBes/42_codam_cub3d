/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 16:35:38 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/05 18:29:10 by fbes          ########   odam.nl         */
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

static int	clear_queue_and_return_zero(t_list *queue, char **temp_lvl, size_t lvl_h)
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
	printf("\t\t\tChecking if %i, %i is outside (lvl_h: %zu)...\n", x, y, game->map->lvl_h);
	if (x == -1 || y == -1 || x == game->map->lvl_h || y == game->map->lvl_w - 1 ||
		temp_lvl[x][y + 1] == '\0' || temp_lvl[x][y + 1] == ' ' ||
		(y == 0 && inside(temp_lvl, x, y)) ||
		temp_lvl[x][y - 1] == '\0' || temp_lvl[x][y - 1] == ' ')
		return (1);
	return (0);
}

static void	scan(t_list **queue, char **temp_lvl, int lx, int rx, int y)
{
	int		added;
	int		x;

	added = 0;
	x = lx;
	printf("x: %d, lx: %d, rx: %d\n", x, lx, rx);
	while (x <= rx)
	{
		printf("\t\tChecking if %i, %i (%c) is inside...\n", x, y, temp_lvl[x][y]);
		if (!inside(temp_lvl, x, y))
			added = 0;
		else if (added == 0)
		{
			ft_lstadd_back(queue, ft_lstnew(new_map_node(x, y, temp_lvl[x][y])));
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
	t_map_node	*helper;
	t_list		*queue;
	t_list		*current;

	printf("Checking if the map is surrounded by walls... Please wait...\n");
	temp_lvl = lvl_copy(game->map);
	if (!temp_lvl)
		return (0);
	x = game->cam.pos_x;
	y = game->cam.pos_y;
	helper = new_map_node(x, y, temp_lvl[x][y]);
	if (!helper)
		return (0);
	queue = ft_lstnew((void *)helper);
	if (!queue)
		return (0);
	while (queue)
	{
		//system("clear");
		current = queue;
		x = ((t_map_node *)current->content)->x;
		y = ((t_map_node *)current->content)->y;
		if (outside(game, temp_lvl, x, y))
			return (clear_queue_and_return_zero(queue, temp_lvl, game->map->lvl_h));
		lx = x;
		printf("\tLXChecking %i, %i (max %zu, %zu): %c...\n", lx - 1 , y, game->map->lvl_h, game->map->lvl_w, temp_lvl[lx - 1][y]);
		while (inside(temp_lvl, lx - 1, y))
		{
			temp_lvl[lx - 1][y] = '*';
			lx--;
			if (outside(game, temp_lvl, lx - 1, y))
				return (clear_queue_and_return_zero(queue, temp_lvl, game->map->lvl_h));
			printf("\tLXChecking %i, %i (max %zu, %zu): %c...\n", lx - 1, y, game->map->lvl_h, game->map->lvl_w, temp_lvl[lx - 1][y]);
		}
		printf("\tXChecking %i, %i (max %zu, %zu): %c...\n", x, y, game->map->lvl_h, game->map->lvl_w, temp_lvl[x][y]);
		while (inside(temp_lvl, x, y))
		{
			temp_lvl[x][y] = '*';
			x++;
			if (outside(game, temp_lvl, x, y))
				return (clear_queue_and_return_zero(queue, temp_lvl, game->map->lvl_h));
			printf("\tXChecking %i, %i (max %zu, %zu): %c...\n", x, y, game->map->lvl_h, game->map->lvl_w, temp_lvl[x][y]);
		}
		queue = queue->next;
		ft_lstdelone(current, &delete_queue_item);
		print_map(*(game->map), temp_lvl);
		printf("\tScan starting from %i, %i (%c), to the top...\n", x - 1, y + 1, temp_lvl[x - 1][y]);
		scan(&queue, temp_lvl, lx, x - 1, y + 1);
		printf("\tScan starting from %i, %i (%c), to the bottom...\n", x - 1, y - 1, temp_lvl[x - 1][y]);
		scan(&queue, temp_lvl, lx, x - 1, y - 1);
	}
	print_map(*(game->map), temp_lvl);
	free_lvl(temp_lvl, game->map->lvl_h);
	return (1);
}
