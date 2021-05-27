/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 16:40:22 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 17:34:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "c3d.h"

// made use of the way integers are stored in memory below.
// integers are stored backwards in memory, and the BMP format
// does not use RGB, but "BGR", so that comes in handy.
// (big-endian vs little-endian)
// there's no need to modify the color value that get_pixel returns,
// as the alpha channel will just get overwritten by the next pixel
// (or, in the case of padding, will be ignored).

static void	write_bmp_line(t_game *game, char **data, int y)
{
	int				x;
	unsigned int	c;

	x = 0;
	while (x < (int)(game->map->res_x))
	{
		c = get_color(&game->mlx->img, x, y);
		if (game->mlx->img.endian == 1)
			c = convert_endian(1, c);
		*(unsigned int *)(*data) = c;
		*data += 3;
		x++;
	}
}

static void	frame_to_bmp_img_data(t_game *game, char *data)
{
	int		y;
	int		padding;

	y = (int)(game->map->res_y) - 1;
	while (y >= 0)
	{
		write_bmp_line(game, &data, y);
		padding = game->map->res_x * 3 % 4;
		while (padding > 0 && padding < 4)
		{
			data++;
			padding++;
		}
		y--;
	}
}

static int	write_bmp(char *bmp, size_t bmp_size, char *file_name)
{
	int		fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > 0)
	{
		if (write(fd, bmp, bmp_size) == (ssize_t)bmp_size)
			return (1);
		else
			return (-51);
	}
	return (-50);
}

static void	set_bmp_header(t_game *game, char *bmp, int *f_size, int *d_offset)
{
	bmp[0] = 0x42;
	bmp[1] = 0x4D;
	ft_memcpy(bmp + 2, f_size, 4);
	ft_memcpy(bmp + 10, d_offset, 4);
	*(int *)(bmp + 14) = 12;
	*(short *)(bmp + 18) = (short)(game->map->res_x);
	*(short *)(bmp + 20) = (short)(game->map->res_y);
	*(short *)(bmp + 22) = 1;
	*(short *)(bmp + 24) = 24;
}

int	export_frame_as_bmp(t_game *game, char *file_name)
{
	char	*bmp;
	int		file_size;
	int		img_data_offset;
	int		write_return_val;
	int		padding_req;

	img_data_offset = 26;
	padding_req = game->map->res_x * 3 % 4;
	if (padding_req > 0)
		padding_req = 4 - padding_req;
	file_size = img_data_offset + game->map->res_y * game->map->res_x * 3
		+ padding_req * game->map->res_y;
	bmp = (char *)ft_calloc(sizeof(char), file_size);
	if (bmp)
	{
		set_bmp_header(game, bmp, &file_size, &img_data_offset);
		frame_to_bmp_img_data(game, bmp + img_data_offset);
		write_return_val = write_bmp(bmp, file_size, file_name);
		free(bmp);
		if (write_return_val < 0)
			return (write_return_val);
		return (1);
	}
	return (-1);
}
