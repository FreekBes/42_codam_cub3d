/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 16:20:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/12 22:28:38 by fbes          ########   odam.nl         */
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

int	config_valid(t_map *map)
{
	if (map->lvl_w == 0 || map->lvl_h == 0)
		return (0);
	if (map->res_x == 0 || map->res_y == 0)
		return (0);
	if (map->col_floor == COLOR_VALUE_UNDEFINED
		|| map->col_ceiling == COLOR_VALUE_UNDEFINED)
		return (0);
	return (1);
}
