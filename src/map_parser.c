/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/12 20:55:57 by fbes          ########   odam.nl         */
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
	else if (ft_strchr("102NSEW", id[0]) != NULL)
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

char	*read_file(char *contents, char *buff, size_t buff_size)
{
	char	*temp;
	size_t	contents_len;

	if (!contents)
	{
		contents = ft_calloc(buff_size + 1, sizeof(char));
		contents_len = 0;
	}
	else
	{
		contents_len = ft_strlen(contents);
		temp = ft_calloc(contents_len + buff_size + 1, sizeof(char));
		ft_memmove(temp, contents, contents_len);
		ft_free(contents);
		contents = temp;
	}
	ft_memmove(contents + contents_len, buff, buff_size);
	return (contents);
}

static void		free_lines(char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i])
			ft_free(lines[i]);
		i++;
	}
	ft_free(lines);
}

// no if-elseif in the while loop below, since stage 2 needs to be run if
// the result of parse_line > 0 as well.

static t_map	*string_to_map(char *str)
{
	t_map	*map;
	char	**lines;
	size_t	i;
	int		stage;
	int		res;

	map = new_map();
	if (map)
	{
		lines = ft_split(str, '\n');
		i = 0;
		stage = 1;
		res = 0;
		while (lines[i])
		{
			if (stage == 1 && parse_line(&map, lines[i]) > 0)
				stage = 2;
			if (stage == 2)
			{
				res = parse_level(&map, lines[i]);
				if (res != 0)
					break;
			}
			i++;
		}
		free_lines(lines);
		print_map(*map, NULL);
		if (res < 0 || !map_characters_valid(map))
			return (ft_free(map));
	}
	return (map);
}

t_map	*parse_map(char *map_file)
{
	t_map	*map;
	int		fd;
	char	*contents;
	void	*buffer;
	int		read_res;

	map = NULL;
	contents = NULL;
	if (!map_filename_valid(map_file))
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), 256);
	if (!buffer)
		return (NULL);
	read_res = read(fd, buffer, 255);
	while(read_res > 0)
	{
		contents = read_file(contents, buffer, 255);
		ft_bzero(buffer, 255);
		read_res = read(fd, buffer, 255);
	}
	if (read_res < 0)
		ft_free(contents);
	else
		map = string_to_map(contents);
	ft_free(buffer);
	close(fd);
	return (map);
}
