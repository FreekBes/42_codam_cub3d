/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 20:24:02 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/28 21:12:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "MLX42/MLX42.h"

static void	create_img(t_mlx_ctx *ctx, t_map *map)
{
	ctx->img = mlx_new_image(ctx->core, map->res_x, map->res_y);
}

static void	catch_max_res_exception(t_map *map)
{
	int32_t		scr_x;
	int32_t		scr_y;

	mlx_get_monitor_size(0, &scr_x, &scr_y);
	if (scr_x == 0 || scr_y == 0)
		return ;
	if (map->res_x > scr_x)
		map->res_x = scr_x;
	if (map->res_y > scr_y)
		map->res_y = scr_y;
}

void	*free_mlx_context(t_mlx_ctx *ctx)
{
	if (ctx->img)
		mlx_delete_image(ctx->core, ctx->img);
	ft_free(ctx);
	return (NULL);
}

t_mlx_ctx	*get_mlx_context(t_map *map, char *win_title)
{
	t_mlx_ctx	*mlx_ctx;

	catch_max_res_exception(map);
	mlx_ctx = (t_mlx_ctx *)malloc(sizeof(t_mlx_ctx));
	if (mlx_ctx)
	{
		mlx_ctx->core = mlx_init(map->res_x, map->res_y, win_title, true);
		if (!mlx_ctx->core)
			return (free_mlx_context(mlx_ctx));
		create_img(mlx_ctx, map);
		if (!mlx_ctx->img)
			return (free_mlx_context(mlx_ctx));
	}
	return (mlx_ctx);
}

void	win_resize(int32_t w, int32_t h, void *game)
{
	mlx_resize_image(((t_game *)game)->mlx->img, w, h);
	((t_game *)game)->map->res_x = w;
	((t_game *)game)->map->res_y = h;
}
