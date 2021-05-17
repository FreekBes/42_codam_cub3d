/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 16:20:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/17 19:08:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	extension_valid(char *file_name, char *ext)
{
	size_t		filename_len;
	size_t		ext_len;

	filename_len = ft_strlen(file_name);
	ext_len = ft_strlen(ext);
	if (filename_len < ext_len)
		return (0);
	if (ft_strncmp(file_name + filename_len - ext_len, ext, ext_len) != 0)
		return (0);
	return (1);
}

int	map_characters_valid(t_map *map)
{
	int		i;
	int		j;
	int		start_found;

	start_found = 0;
	i = 0;
	while (i < map->lvl_h)
	{
		j = 0;
		while (j < map->lvl_w)
		{
			if (!ft_strchr(" 012NSEW", map->lvl[i][j]))
				return (0);
			if (map->lvl[i][j] && ft_strchr("NSEW", map->lvl[i][j]))
			{
				if (start_found)
					return (0);
				start_found = 1;
			}
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
	if (map->res_x <= 0 || map->res_y <= 0)
		return (0);
	if (map->col_floor == COLOR_VALUE_UNDEFINED
		|| map->col_ceiling == COLOR_VALUE_UNDEFINED)
		return (0);
	return (1);
}
