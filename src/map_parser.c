/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 11:52:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_config_attr_more(t_map **map, char *c, char *id)
{
	if (id[0] == 'R' && id[1] == ' ')
	{
		if ((*map)->res_x > 0 || (*map)->res_y > 0)
			return (-3);
		if (valid_config_number(c, 1))
		{
			(*map)->res_x = ft_atoi(c);
			c = skip_spaces(skip_non_spaces(c));
			if (valid_config_number(c, 0))
				(*map)->res_y = ft_atoi(c);
		}
	}
	else if (id[0] == 'F' && id[1] == ' ')
	{
		if (parse_color_map(&(*map)->col_floor, &c) < 0)
			return (-4);
	}
	else if (id[0] == 'C' && id[1] == ' ')
	{
		if (parse_color_map(&(*map)->col_ceiling, &c) < 0)
			return (-5);
	}
	else if (ft_strchr("102NSEW", id[0]) != NULL)
		return (1);
	return (0);
}

static int	parse_config_attr(t_map **map, char *c, char *id)
{
	int		res;

	if (ft_strlen(id) < 3)
		return (-2);
	if (id[0] == 'N' && id[1] == 'O' && id[2] == ' ')
		res = init_texture(&(*map)->tex_no, c);
	else if (id[0] == 'S' && id[1] == 'O' && id[2] == ' ')
		res = init_texture(&(*map)->tex_so, c);
	else if (id[0] == 'W' && id[1] == 'E' && id[2] == ' ')
		res = init_texture(&(*map)->tex_we, c);
	else if (id[0] == 'E' && id[1] == 'A' && id[2] == ' ')
		res = init_texture(&(*map)->tex_ea, c);
	else if (id[0] == 'S' && id[1] == ' ')
		res = init_texture(&(*map)->tex_sprite, c);
	else
		return (parse_config_attr_more(map, c, id));
	return (res);
}

static int	parse_config(t_map **map, char *line)
{
	char	*c;
	char	*id;

	id = skip_spaces(line);
	if (*id == '\0')
		return (0);
	c = skip_spaces(skip_non_spaces(id));
	return (parse_config_attr(map, c, id));
}

// no if-elseif in the function below, since stage 2 needs to be run if
// the result of parse_line > 0 as well.

static int	parse_line(int *stage, t_map **map, char *line, int *res)
{
	if (*stage == 1)
	{
		*res = parse_config(map, line);
		if (*res > 0)
			*stage = 2;
		else if (*res < 0)
			return (-1);
	}
	else if (*stage == 1 && *res < 0)
		return (-1);
	if (*stage == 2)
	{
		*res = parse_level(map, line);
		if (*res != 0)
			return (1);
	}
	return (0);
}

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
		if (!lines)
			return (NULL);
		i = 0;
		stage = 1;
		res = 0;
		while (lines[i] && res >= 0)
		{
			if (parse_line(&stage, &map, lines[i], &res) > 0)
				break ;
			i++;
		}
		free_lines(lines);
		if (res < 0 || !config_valid(map) || !map_characters_valid(map))
			return (ft_free(map));
	}
	return (map);
}
