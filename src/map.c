/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 21:11:22 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 12:18:42 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_map	*new_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map)
	{
		map->res_x = 0;
		map->res_y = 0;
		map->lvl = NULL;
		map->lvl_w = 0;
		map->lvl_h = 0;
		map->tex_no = NULL;
		map->tex_ea = NULL;
		map->tex_so = NULL;
		map->tex_we = NULL;
		map->tex_sprite = NULL;
		map->col_ceiling = COLOR_VALUE_UNDEFINED;
		map->col_floor = COLOR_VALUE_UNDEFINED;
		map->sprites = NULL;
	}
	return (map);
}

int	free_lvl(char **lvl, size_t lvl_h)
{
	size_t	i;

	i = 0;
	while (i < lvl_h)
	{
		if (lvl[i])
			free(lvl[i]);
		i++;
	}
	free(lvl);
	return (0);
}

void	free_map(void *mlx, t_map *map)
{
	if (map->tex_no)
		free_texture(mlx, map->tex_no);
	if (map->tex_so)
		free_texture(mlx, map->tex_so);
	if (map->tex_we)
		free_texture(mlx, map->tex_we);
	if (map->tex_ea)
		free_texture(mlx, map->tex_ea);
	if (map->tex_sprite)
		free_texture(mlx, map->tex_sprite);
	if (map->lvl)
		free_lvl(map->lvl, map->lvl_h);
	if (map->sprites)
		ft_lstclear(&map->sprites, &item_free_simple);
	free(map);
}

// copy a level to a new string, useful for operations
// that would interfere with a playthrough, like changing
// all 0 characters to * characters.

char	**lvl_copy(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * map->lvl_h);
	if (copy)
	{
		i = 0;
		while (i < map->lvl_h)
		{
			copy[i] = ft_calloc(map->lvl_w, sizeof(char));
			if (copy[i])
				ft_memcpy(copy[i], map->lvl[i], map->lvl_w);
			i++;
		}
	}
	return (copy);
}
