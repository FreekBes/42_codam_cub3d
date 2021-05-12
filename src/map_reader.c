/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 21:10:11 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/12 21:16:22 by fbes          ########   odam.nl         */
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
