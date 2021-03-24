/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:57:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/24 19:33:44 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_map	*new_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	return (map);
}

static char	*skip_spaces(char *c)
{
	while (*c == ' ')
		c++;
	return (c);
}

static char	*skip_non_spaces(char *c)
{
	while (*c != ' ')
		c++;
	return (c);
}

static t_col_rgba	*parse_color(char **c)
{
	t_col_rgba	*color;

	color = (t_col_rgba *)malloc(sizeof(t_col_rgba));
	color->r = ft_atoi(*c);
	*c = ft_strchr(*c, ',') + 1;
	*c = skip_spaces(*c);
	color->g = ft_atoi(*c);
	*c = ft_strchr(*c, ',') + 1;
	*c = skip_spaces(*c);
	color->b = ft_atoi(*c);
	color->a = 255;
	return (color);
}

static void	parse_line(t_map **map, char *line)
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
		(*map)->col_floor = parse_color(&c);
	else if (id[0] == 'C')
		(*map)->col_ceiling = parse_color(&c);
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
					parse_line(&map, *line);
				if (*line)
					free(*line);
				if (result < 0)
					return (NULL);
			}
		}
		free(line);
	}
	close(fd);
	return (map);
}
