/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:38:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 17:38:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "MLX42/MLX42.h"

void	put_rect(t_mlx_ctx *mlx, t_rect *rect)
{
	t_coords		pos;

	pos.y = rect->y;
	while (pos.y < rect->h + rect->y)
	{
		pos.x = rect->x;
		while (pos.x < rect->w + rect->x)
		{
			// put_pixel(mlx, &pos, rect->c, 0);
			mlx_putpixel(mlx->img, pos.x, pos.y, 0);
			pos.x++;
		}
		pos.y++;
	}
}
