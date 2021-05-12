/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/12 21:15:12 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

// no if-elseif in the while loop below, since stage 2 needs to be run if
// the result of parse_line > 0 as well.

t_map	*string_to_map(char *str)
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
		if (res < 0 || !map_characters_valid(map))
			return (ft_free(map));
	}
	return (map);
}
