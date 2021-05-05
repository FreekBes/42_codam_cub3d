/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/05 20:09:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map	*new_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map)
	{
		map->lvl = NULL;
		map->lvl_w = 0;
		map->lvl_h = 0;
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
	free(map);
}

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

static char	*skip_spaces(char *c)
{
	while (*c && *c == ' ')
		c++;
	return (c);
}

static char	*skip_non_spaces(char *c)
{
	while (*c && *c != ' ')
		c++;
	return (c);
}

static unsigned int	parse_color_map(char **c)
{
	t_col_rgba		t_col;

	t_col.r = ft_atoi(*c);
	*c = ft_strchr(*c, ',');
	if (!*c)
		return (0);
	*c = skip_spaces(*c + 1);
	t_col.g = ft_atoi(*c);
	*c = ft_strchr(*c, ',');
	if (!*c)
		return (0);
	*c = skip_spaces(*c + 1);
	t_col.b = ft_atoi(*c);
	t_col.a = 0;
	return (color_to_uint(&t_col));
}

static int	parse_line(t_map **map, char *line)
{
	char	*c;
	char	*id;

	id = skip_spaces(line);
	c = skip_spaces(skip_non_spaces(id));
	if (id[0] == 'R')
	{
		(*map)->res_x = ft_atoi(c);
		c = skip_spaces(skip_non_spaces(c));
		(*map)->res_y = ft_atoi(c);
	}
	else if (id[0] == 'N' && id[1] == 'O')
		(*map)->tex_no = init_texture(c);
	else if (id[0] == 'S' && id[1] == 'O')
		(*map)->tex_so = init_texture(c);
	else if (id[0] == 'W' && id[1] == 'E')
		(*map)->tex_we = init_texture(c);
	else if (id[0] == 'E' && id[1] == 'A')
		(*map)->tex_ea = init_texture(c);
	else if (id[0] == 'S')
		(*map)->tex_sprite = init_texture(c);
	else if (id[0] == 'F')
		(*map)->col_floor = parse_color_map(&c);
	else if (id[0] == 'C')
		(*map)->col_ceiling = parse_color_map(&c);
	else if (id[0] == '1')
		return (1);
	return (0);
}

static int	remalloc_lvl_line(char **line, size_t len)
{
	char	*new_line;
	size_t	old_len;

	old_len = ft_strlen(*line);
	new_line = ft_realloc(*line, old_len, len + 1);
	if (!new_line)
		return (-1);
	ft_memset(new_line + old_len, ' ', len - old_len);
	new_line[len - 1] = '\0';
	*line = new_line;
	return (1);
}

static int	remalloc_level(char **level, int lines, int len)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		if (remalloc_lvl_line(&level[i], len) < 0)
			return (-1);
		i++;
	}
	return (1);
}

static int	parse_level(t_map **map, char *line)
{
	char	*c;
	int		len;

	c = line;
	len = (int)ft_strlen(line);
	if (len == 0)
		return (1);
	if (len > (*map)->lvl_w)
	{
		(*map)->lvl_w = len;
		if (remalloc_level((*map)->lvl, (*map)->lvl_h, (*map)->lvl_w) < 0)
			return (-1);
	}
	(*map)->lvl_h++;
	(*map)->lvl = ft_realloc((*map)->lvl, ((*map)->lvl_h - 1) * sizeof(char *), (*map)->lvl_h * sizeof(char *));
	if (!(*map)->lvl)
		return (-1);
	(*map)->lvl[(*map)->lvl_h - 1] = ft_calloc(sizeof(char), (*map)->lvl_w + 1);
	if (!(*map)->lvl[(*map)->lvl_h - 1])
		return (-1);
	ft_memmove((*map)->lvl[(*map)->lvl_h - 1], line, len);
	return (0);
}

t_map	*parse_map(char *map_file)
{
	t_map	*map;
	int		fd;
	char	**line;
	int		res_gnl;
	int		res_parser;

	if (!map_filename_valid(map_file))
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = (char **)malloc(sizeof(char *));
	map = NULL;
	if (line)
	{
		map = new_map();
		if (map)
		{
			res_gnl = 1;
			while (res_gnl > 0)
			{
				res_gnl = ft_get_next_line(fd, line);
				if (res_gnl >= 0)
				{
					if (parse_line(&map, *line) > 0)
					{
						res_parser = parse_level(&map, *line);
						break;
					}
				}
				if (*line)
					ft_free(*line);
				if (res_gnl < 0)
				{
					close(fd);
					ft_free(line);
					return (ft_free(map));
				}
			}
			res_gnl = 1;
			while (res_gnl > 0)
			{
				res_gnl = ft_get_next_line(fd, line);
				if (res_gnl >= 0)
				{
					res_parser = parse_level(&map, *line);
					if (res_parser > 0)
						break;
					if (res_parser < 0)
					{
						close(fd);
						ft_free(line);
						return (ft_free(map));
					}
				}
				if (*line)
					ft_free(*line);
				if (res_gnl < 0)
				{
					close(fd);
					ft_free(line);
					return (ft_free(map));
				}
			}
			ft_free(line);
			if (!map_characters_valid(map))
			{
				close(fd);
				return (ft_free(map));
			}
		}
	}
	close(fd);
	return (map);
}
