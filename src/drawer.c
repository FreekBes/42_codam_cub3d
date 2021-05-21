/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:38:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/21 15:11:53 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *img, int x, int y, unsigned int c)
{
	char	*dst;

	dst = img->address + y * img->line_size + x * (img->bits_per_pixel / 8);
	*(unsigned int *)dst = c;
}

void	put_pixel_endian(t_img *img, t_coords *p, unsigned int c, int c_endian)
{
	char	*dst;

	dst = img->address + p->y * img->line_size
		+ p->x * (img->bits_per_pixel / 8);
	if (img->endian != c_endian)
		c = convert_endian(c_endian, c);
	*(unsigned int *)dst = c;
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->address + y * img->line_size + x * (img->bits_per_pixel / 8);
	return (*(unsigned int *)dst);
}

void	put_rect(t_img *img, t_rect *rect)
{
	t_coords		pos;

	pos.y = rect->y;
	while (pos.y < rect->h + rect->y)
	{
		pos.x = rect->x;
		while (pos.x < rect->w + rect->x)
		{
			put_pixel_endian(img, &pos, rect->c, 0);
			pos.x++;
		}
		pos.y++;
	}
}

void	clear_img(t_img *img, t_map *map)
{
	t_rect	temp_rect;

	temp_rect.c = 0x00000000;
	temp_rect.x = 0;
	temp_rect.y = 0;
	temp_rect.w = map->res_x;
	temp_rect.h = map->res_y;
	put_rect(img, &temp_rect);
}
