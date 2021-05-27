/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:38:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:51:25 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void	put_pixel(t_mlx_ctx *mlx, int x, int y, unsigned int c)
{
	char	*dst;

	dst = mlx->img.address + y * mlx->img.line_size
		+ x * (mlx->img.bits_per_pixel / 8);
	*(unsigned int *)dst = mlx_get_color_value(mlx->core, c);
}

void	put_pixel_endian(t_mlx_ctx *mlx, t_coords *pos,
			unsigned int c, int c_endian)
{
	char	*dst;

	dst = mlx->img.address + pos->y * mlx->img.line_size
		+ pos->x * (mlx->img.bits_per_pixel / 8);
	if (mlx->img.endian != c_endian)
		c = convert_endian(c_endian, c);
	*(unsigned int *)dst = mlx_get_color_value(mlx->core, c);
}

void	put_rect(t_mlx_ctx *mlx, t_rect *rect)
{
	t_coords		pos;

	pos.y = rect->y;
	while (pos.y < rect->h + rect->y)
	{
		pos.x = rect->x;
		while (pos.x < rect->w + rect->x)
		{
			put_pixel_endian(mlx, &pos, rect->c, 0);
			pos.x++;
		}
		pos.y++;
	}
}
