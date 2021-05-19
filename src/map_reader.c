/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 21:10:11 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 15:22:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*append_buffer(char *contents, char *buff, size_t buff_size)
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
		if (!temp)
			return (NULL);
		ft_memmove(temp, contents, contents_len);
		ft_free(contents);
		contents = temp;
	}
	if (!contents)
		return (NULL);
	ft_memmove(contents + contents_len, buff, buff_size);
	return (contents);
}

static int	init_map_parser(char *map_file, char **cont, int *fd, void **buff)
{
	*cont = NULL;
	if (!extension_valid(map_file, ".cub")
		&& !extension_valid(map_file, ".CUB"))
		return (-30);
	*fd = open(map_file, O_RDONLY);
	if (*fd < 0)
		return (-31);
	*buff = ft_calloc(sizeof(char), 256);
	if (!*buff)
		return (-6);
	return (1);
}

t_map	*parse_map(char *map_file, int *err)
{
	t_map	*map;
	int		fd;
	char	*contents;
	void	*buffer;
	int		read_res;

	map = NULL;
	*err = init_map_parser(map_file, &contents, &fd, &buffer);
	if (*err < 0)
		return (NULL);
	read_res = read(fd, buffer, 255);
	while (read_res > 0)
	{
		contents = append_buffer(contents, buffer, 255);
		if (!contents)
		{
			*err = -6;
			return (NULL);
		}
		ft_bzero(buffer, 255);
		read_res = read(fd, buffer, 255);
	}
	if (read_res == 0)
		map = config_to_map(ft_split(contents, '\n'), err);
	else if (read_res < 0)
	{
		*err = -33;
		return (NULL);
	}
	ft_free(contents);
	ft_free(buffer);
	close(fd);
	return (map);
}
