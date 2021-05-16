/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 21:10:11 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/16 20:22:59 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*read_file(char *contents, char *buff, size_t buff_size)
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

static int	init_map_parser(char *map_file, char **cont, int *fd, void **buff)
{
	*cont = NULL;
	if (!map_filename_valid(map_file))
		return (-1);
	*fd = open(map_file, O_RDONLY);
	if (*fd < 0)
		return (-1);
	*buff = ft_calloc(sizeof(char), 256);
	if (!*buff)
		return (-1);
	return (1);
}

t_map	*parse_map(char *map_file)
{
	t_map	*map;
	int		fd;
	char	*contents;
	void	*buffer;
	int		read_res;

	map = NULL;
	if (init_map_parser(map_file, &contents, &fd, &buffer) < 0)
		return (NULL);
	read_res = read(fd, buffer, 255);
	while (read_res > 0)
	{
		contents = read_file(contents, buffer, 255);
		ft_bzero(buffer, 255);
		read_res = read(fd, buffer, 255);
	}
	if (read_res == 0)
		map = string_to_map(contents);
	ft_free(contents);
	ft_free(buffer);
	close(fd);
	return (map);
}
