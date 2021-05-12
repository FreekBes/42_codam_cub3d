/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/12 22:23:30 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_config_attr(t_map **map, char *c, char *id)
{
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

static int	parse_config(t_map **map, char *line)
{
	char	*c;
	char	*id;

	id = skip_spaces(line);
	c = skip_spaces(skip_non_spaces(id));
	return (parse_config_attr(map, c, id));
}

// no if-elseif in the function below, since stage 2 needs to be run if
// the result of parse_line > 0 as well.

static int	parse_line(int *stage, t_map **map, char *line, int *res)
{
	if (*stage == 1 && parse_config(map, line) > 0)
		*stage = 2;
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
		i = 0;
		stage = 1;
		res = 0;
		while (lines[i])
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
