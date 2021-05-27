/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

// parse resolution, floor and ceiling colors in the config.
// the function returns 1 as soon as a start of a map was found,
// instead of a config identifier.

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
			else
				return (-7);
		}
		else
			return (-7);
	}
	else if (id[0] == 'F' && id[1] == ' ')
		return (parse_color_map(&(*map)->col_floor, &c));
	else if (id[0] == 'C' && id[1] == ' ')
		return (parse_color_map(&(*map)->col_ceiling, &c));
	else if (ft_strchr("102NSEW", id[0]) != NULL)
		return (1);
	return (0);
}

// parse paths to textures in the config file.
// if the config identifier is not for a texture,
// parse_config_attr_more is ran and returned,
// where more config attributes are parsed.

static int	parse_config_attr(t_map **map, char *c, char *id)
{
	int		res;

	if (ft_strlen(id) < 3 && ft_strchr("102NSEW", id[0]) == NULL)
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

// no if-elseif in the root of the function below,
// since stage 2 needs to be run if the result
// of parse_line > 0 as well (we've then found the map,
// and the current line then needs to be parsed as such).

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

// read a configuration, line by line.
// *config holds an array of strings, each string being one line
// in a .cub file. This method assumes **config has been created
// by ft_split, and checks for NULL + frees it as such.

t_map	*config_to_map(char **config, int *err)
{
	t_map	*map;
	size_t	i;
	int		stage;

	if (!config)
		return (NULL);
	map = new_map();
	if (map)
	{
		i = 0;
		stage = 1;
		*err = 0;
		while (config[i] && *err >= 0)
		{
			if (parse_line(&stage, &map, config[i], err) > 0)
				break ;
			i++;
		}
		free_lines(config);
		if (*err < 0 || config_valid(map, err) < 0
			|| map_characters_valid(map, err) < 0)
			return (free_map(NULL, map));
	}
	return (map);
}
