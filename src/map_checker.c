/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 16:20:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/30 17:52:27 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_filename_valid(char *map_file)
{
	size_t		filename_len;

	filename_len = ft_strlen(map_file);
	if (filename_len < 5)
		return (0);
	if (ft_strncmp(map_file + filename_len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	map_characters_valid(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->lvl_h)
	{
		j = 0;
		while (j < map->lvl_w)
		{
			if (!ft_strchr(" 012NSEW", map->lvl[i][j]))
				return (0);
			j++;
		}
		i++;
	}
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
			if (ft_strchr("NSEW", game->map->lvl[i][j]))
			{
				game->cam.pos_x = i + 0.5;
				game->cam.pos_y = j + 0.5;
				if (game->map->lvl[i][j] == 'N' || game->map->lvl[i][j] == 'S')
				{
					game->cam.dir_y = 0;
					game->cam.plane_x = 0;
				}
				else
				{
					game->cam.dir_x = 0;
					game->cam.plane_y = 0;
				}
				if (game->map->lvl[i][j] == 'N')
				{
					game->cam.dir_x = -1;
					game->cam.plane_y = 0.66;
				}
				else if (game->map->lvl[i][j] == 'S')
				{
					game->cam.dir_x = 1;
					game->cam.plane_y = -0.66;
				}
				else if (game->map->lvl[i][j] == 'W')
				{
					game->cam.dir_y = -1;
					game->cam.plane_x = -0.66;
				}
				else
				{
					game->cam.dir_y = 1;
					game->cam.plane_x = 0.66;
				}
				return (1);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

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

int	map_surrounded_by_walls(t_game *game)
{
	char		**temp_lvl;
	t_list		*queue;
	t_list		*current;
	t_map_node	*helper;
	int			x;
	int			y;

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
		current = queue;
		x = ((t_map_node *)current->content)->x;
		y = ((t_map_node *)current->content)->y;
		system("clear");
		printf("Checking %i, %i (max %zu, %zu)...\n", x, y, game->map->lvl_h, game->map->lvl_w);
		if (x == 0 || y == 0 || x == game->map->lvl_h - 1 ||
			((t_map_node *)current->content)->c == '\0' || ((t_map_node *)current->content)->c == ' ')
			return (clear_queue_and_return_zero(queue, temp_lvl, game->map->lvl_h));
		if (ft_strchr("02NSEW", ((t_map_node *)current->content)->c))
		{
			temp_lvl[x][y] = '#';
			if (y > 0 && ft_strchr(" 02NSEW", temp_lvl[x][y - 1]))									// W
				ft_lstadd_back(&queue, ft_lstnew(new_map_node(x, y - 1, temp_lvl[x][y - 1])));
			if (y < game->map->lvl_w && ft_strchr(" 02NSEW", temp_lvl[x][y + 1]))					// E
				ft_lstadd_back(&queue, ft_lstnew(new_map_node(x, y + 1, temp_lvl[x][y + 1])));
			if (x > 0 && ft_strchr(" 02NSEW", temp_lvl[x - 1][y]))									// N
				ft_lstadd_back(&queue, ft_lstnew(new_map_node(x - 1, y, temp_lvl[x - 1][y])));
			if (x < game->map->lvl_h - 1 && ft_strchr(" 02NSEW", temp_lvl[x + 1][y]))				// S
				ft_lstadd_back(&queue, ft_lstnew(new_map_node(x + 1, y, temp_lvl[x + 1][y])));
			print_map(*(game->map), temp_lvl);
			temp_lvl[x][y] = '*';
		}
		queue = queue->next;
		ft_lstdelone(current, &delete_queue_item);
	}
	print_map(*(game->map), temp_lvl);
	free_lvl(temp_lvl, game->map->lvl_h);
	return (1);
}
