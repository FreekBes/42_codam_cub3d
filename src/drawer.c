/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:38:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/14 15:44:30 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->address + y * img->line_size + x * (img->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	put_rect(t_img *img, t_rect *rect)
{
	unsigned int	temp_x;
	unsigned int	temp_y;

	temp_y = rect->y;
	while (temp_y < rect->h + rect->y)
	{
		temp_x = rect->x;
		while (temp_x < rect->w + rect->x)
		{
			put_pixel(img, temp_x, temp_y, rect->c);
			temp_x++;
		}
		temp_y++;
	}
}

void	put_vert_line(t_img *img, int x, int drawStart, int drawEnd, unsigned int color)
{
	while (drawStart < drawEnd)
	{
		put_pixel(img, x, drawStart, color);
		drawStart++;
	}
}

void	put_hori_line(t_img *img, int y, int drawStart, int drawEnd, unsigned int color)
{
	while (drawStart < drawEnd)
	{
		put_pixel(img, drawStart, y, color);
		drawStart++;
	}
}
