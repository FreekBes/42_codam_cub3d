/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:38:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/21 15:52:57 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	clear_img(t_mlx_ctx *mlx, t_map *map)
{
	t_rect	temp_rect;

	temp_rect.c = 0x00000000;
	temp_rect.x = 0;
	temp_rect.y = 0;
	temp_rect.w = map->res_x;
	temp_rect.h = map->res_y;
	put_rect(mlx, &temp_rect);
}
