/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:40:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/07 20:00:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	size_t	i;

	if (map->tex_no)
		free(map->tex_no);
	if (map->tex_so)
		free(map->tex_so);
	if (map->tex_we)
		free(map->tex_we);
	if (map->tex_ea)
		free(map->tex_ea);
	if (map->lvl)
	{
		i = 0;
		while (i < map->lvl_h)
		{
			if (map->lvl[i])
				free(map->lvl[i]);
			i++;
		}
		free(map->lvl);
	}
	free(map);
}

static int	exit_game(t_game game, char *error_msg)
{
	if (error_msg)
		print_error(error_msg);
	free_mlx_context(game.mlx);
	free_map(game.map);
	//system("leaks cub3D");
	exit(0);
	return (0);
}

static int	exit_hook(t_game *game)
{
	return (exit_game(*game, NULL));
}

static void	render_floor_ceil(t_game *game)
{
	t_rect	ceil_rect;
	t_rect	floor_rect;

	ceil_rect.x = 0;
	ceil_rect.y = 0;
	ceil_rect.w = game->map->res_x;
	ceil_rect.h = game->map->res_y * 0.5;
	ceil_rect.c = game->map->col_ceiling;
	put_rect(game->mlx->img, &ceil_rect);
	floor_rect.x = 0;
	floor_rect.y = game->map->res_y * 0.5;
	floor_rect.w = game->map->res_x;
	floor_rect.h = floor_rect.y;
	floor_rect.c = game->map->col_floor;
	put_rect(game->mlx->img, &floor_rect);
}

static void	set_starting_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->lvl_h)
	{
		j = 0;
		while (j < game->map->lvl_w)
		{
			if (ft_strchr("NSEW", game->map->lvl[i][j]))
			{
				game->cam.posX = j;
				game->cam.posY = i;
				game->cam.dirX = -1;
				game->cam.dirY = 0;
				return;
			}
			j++;
		}
		i++;
	}
}

static int	render_next_frame(t_game *game)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;

	render_floor_ceil(game);
	x = 0;
	while (x < game->map->res_x)
	{
		cameraX = 2 * x / (double)game->map->res_x - 1;
		rayDirX = game->cam.dirX + game->cam.planeX * cameraX;
		rayDirY = game->cam.dirY + game->cam.planeY * cameraX;
		mapX = (int)game->cam.posX;
		mapY = (int)game->cam.posY;
		deltaDistX = ft_abs(1 / rayDirX);
		deltaDistY = ft_abs(1 / rayDirX);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->cam.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->cam.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->cam.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->cam.posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map->lvl[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->cam.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->cam.posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(game->map->res_y / perpWallDist);
		x++;
	}
	return (mlx_put_image_to_window(game->mlx->core, game->mlx->win,
		game->mlx->img->img_ptr, 0, 0));
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc < 2)
		return (print_error("No map specified as first argument"));
	game.cam.planeY = 0.66;
	game.map = parse_map(argv[1]);
	set_starting_pos(&game);
	if (!game.map)
		return (print_error("Failed to parse map"));
	print_map(*(game.map));
	game.mlx = get_mlx_context(game.map, argv[0]);
	if (!game.mlx)
		exit_game(game, "Failed to open MLX window");
	mlx_hook(game.mlx->win, 17, 0, &exit_hook, &game);
	mlx_loop_hook(game.mlx->core, render_next_frame, &game);
	mlx_loop(game.mlx->core);
	return (exit_game(game, NULL));
}
