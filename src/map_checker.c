/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 16:20:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

// check if *file_name ends with *ext extension.
// *ext should include the dot.

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

int	map_characters_valid(t_map *map, int *err)
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
				return (set_err(err, -40));
			if (map->lvl[i][j] && ft_strchr("NSEW", map->lvl[i][j]))
			{
				if (start_found)
					return (set_err(err, -41));
				start_found = 1;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	config_valid(t_map *map, int *err)
{
	if (map->res_x == -1 || map->res_y == -1)
		return (set_err(err, -43));
	if (!map->tex_no || !map->tex_so || !map->tex_ea
		|| !map->tex_we || !map->tex_sprite)
		return (set_err(err, -66));
	else if (map->res_x <= 0 || map->res_y <= 0)
		return (set_err(err, -7));
	if (map->lvl_w == 0 || map->lvl_h == 0)
		return (set_err(err, -42));
	if (map->col_floor == COLOR_VALUE_UNDEFINED
		|| map->col_ceiling == COLOR_VALUE_UNDEFINED)
		return (set_err(err, -44));
	return (1);
}
