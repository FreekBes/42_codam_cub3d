/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 21:24:49 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 13:46:17 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	remalloc_lvl_line(char **line, size_t len)
{
	char	*new_line;
	size_t	old_len;

	old_len = ft_strlen(*line);
	new_line = ft_realloc(*line, old_len, len + 1);
	if (!new_line)
		return (-6);
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
			return (-6);
		i++;
	}
	return (1);
}

// parse a level, line by line. if a line is bigger than any of the lines
// previously parsed, all previous lines are re-allocated with this new
// size, to make sure the level is always "rectangular in memory".

int	parse_level(t_map **map, char *line)
{
	int		len;

	len = (int)ft_strlen(line);
	if (len == 0)
		return (1);
	if (len > (*map)->lvl_w)
	{
		(*map)->lvl_w = len;
		if (remalloc_level((*map)->lvl, (*map)->lvl_h, (*map)->lvl_w) < 0)
			return (-6);
	}
	(*map)->lvl_h++;
	(*map)->lvl = ft_realloc((*map)->lvl, ((*map)->lvl_h - 1) * sizeof(char *),
			(*map)->lvl_h * sizeof(char *));
	if (!(*map)->lvl)
		return (-6);
	(*map)->lvl[(*map)->lvl_h - 1] = ft_calloc(sizeof(char), (*map)->lvl_w + 1);
	if (!(*map)->lvl[(*map)->lvl_h - 1])
		return (-6);
	ft_memmove((*map)->lvl[(*map)->lvl_h - 1], line, len);
	return (0);
}
