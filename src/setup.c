/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 19:51:04 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 17:28:50 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "c3d_game_errors.h"

void	init_game(t_game *game)
{
	game->map = NULL;
	game->mlx = NULL;
	game->cam.speed_mod = 1;
	game->cam.mouse_sens = CAM_DEFAULT_MOUSE_SENSITIVITY;
	game->cam.z_buffer = NULL;
}

void	setup_game(t_game *game, char **argv)
{
	int		err;

	game->map = parse_map(argv[1], &err);
	if (!game->map)
		exit_game(game, ft_abs(err), NULL, get_config_error(&err));
	if (set_starting_pos(game) < 0)
		exit_game(game, 100, ERR_START_POS, NULL);
	if (!map_surrounded_by_walls(game))
		exit_game(game, 101, ERR_MAP_WALLS_MISSING, NULL);
	game->mlx = get_mlx_context(game->map, argv[0]);
	if (!game->mlx)
		exit_game(game, 102, ERR_CREATE_MLX_CONTEXT, NULL);
	err = parse_textures(game);
	if (err < 0)
		exit_game(game, ft_abs(err), ERR_TEXTURE_PARSE, get_config_error(&err));
	parse_sprites(game);
	game->cam.z_buffer = (double *)malloc(sizeof(double) * game->map->res_x);
	if (!game->cam.z_buffer)
		exit_game(game, 104, ERR_Z_BUFFER_ALLOC, NULL);
}

void	setup_args(int argc, char **argv, t_game *game)
{
	game->bmp_export = 0;
	if (argc > 2)
	{
		if (ft_strncmp(argv[2], "--save", 7) == 0)
			game->bmp_export = 1;
		else
			exit_game(game, 107, ERR_INVALID_ARG, NULL);
	}
	if (argc < 2)
		exit_game(game, 108, ERR_CONF_MISSING, NULL);
}
