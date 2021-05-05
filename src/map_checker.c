/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 16:20:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/05 18:30:16 by fbes          ########   odam.nl         */
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
