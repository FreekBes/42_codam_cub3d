/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/14 16:06:19 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map	*new_map(void)
{
	t_map	*map;
	char	temp[5][5] = {
			{'1', '1', '1', '1', '1'},
			{'1', '0', '0', '0', '1'},
			{'1', '0', '0', '0', '1'},
			{'1', '0', '0', 'N', '1'},
			{'1', '1', '1', '1', '1'}
		};
	int		i;

	map = (t_map *)malloc(sizeof(t_map));
	if (map)
	{
		map->lvl_w = 5;
		map->lvl_h = 5;
		map->lvl = (char **)malloc(sizeof(char *) * 5);
		i = 0;
		while (i < 5)
		{
			map->lvl[i] = ft_strdup(temp[i]);
			i++;
		}
	}
	return (map);
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
	unsigned int	col;

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
		(*map)->tex_no = ft_strdup(c);
	else if (id[0] == 'S' && id[1] == 'O')
		(*map)->tex_so = ft_strdup(c);
	else if (id[0] == 'W' && id[1] == 'E')
		(*map)->tex_we = ft_strdup(c);
	else if (id[0] == 'E' && id[1] == 'A')
		(*map)->tex_ea = ft_strdup(c);
	else if (id[0] == 'S')
		(*map)->tex_sprite = ft_strdup(c);
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
	new_line = ft_realloc(*line, old_len, len);
	if (!new_line)
		return (-1);
	ft_memset(new_line + old_len, ' ', len - old_len);
	new_line[len - 1] = '\0';
	if (*line)
		free(*line);
	*line = new_line;
	return (1);
}

static int	remalloc_level(char **level, size_t lines, size_t len)
{
	size_t	i;

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
	size_t	len;

	c = line;
	len = ft_strlen(line);
	if (len == 0)
		return (1);
	if (len > (*map)->lvl_w)
	{
		(*map)->lvl_w = len;
		if (remalloc_level((*map)->lvl, (*map)->lvl_h, (*map)->lvl_w) < 0)
			return (-1);
	}
	(*map)->lvl_h++;
	if (!(*map)->lvl)
		(*map)->lvl = ft_calloc(sizeof(char *), (*map)->lvl_h);
	if (!(*map)->lvl)
		return (-1);
	else if (!ft_realloc((*map)->lvl, (*map)->lvl_h - 1, (*map)->lvl_h))
		return (-1);
	(*map)->lvl[(*map)->lvl_h - 1] = ft_calloc(sizeof(char), (*map)->lvl_w);
	if (!(*map)->lvl[(*map)->lvl_h - 1])
		return (-1);
	ft_memmove((*map)->lvl[(*map)->lvl_h - 1], line, len);
	return (1);
}

t_map	*parse_map(char *map_file)
{
	t_map	*map;
	int		fd;
	char	**line;
	int		result;

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
			result = 1;
			while (result > 0)
			{
				result = ft_get_next_line(fd, line);
				if (result >= 0)
				{
					if (parse_line(&map, *line) > 0)
						break;
				}
				if (*line)
					free(*line);
				if (result < 0)
					return (ft_free(map));
			}
			/*
			result = 1;
			while (result > 0)
			{
				result = ft_get_next_line(fd, line);
				if (result >= 0)
				{
					result = parse_level(&map, *line);
					if (result > 0)
						break;
					if (result < 0)
						return (ft_free(map));
				}
				if (*line)
					free(*line);
				if (result < 0)
					return (ft_free(map));
			}
			*/
		}
		free(line);
	}
	close(fd);
	return (map);
}
