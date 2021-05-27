/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 19:51:04 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:07:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "c3d_game_errors.h"

void	setup_map(t_game *game, int save_bmp, char **argv)
{
	int		err;

	game->cam.speed_mod = 1;
	game->cam.mouse_sens = CAM_DEFAULT_MOUSE_SENSITIVITY;
	game->cam.z_buffer = NULL;
	game->map = parse_map(argv[1], &err);
	if (!game->map)
		exit_game(game, ft_abs(err), NULL, get_config_error(&err));
	if (set_starting_pos(game) < 0)
		exit_game(game, 100, ERR_START_POS, NULL);
	if (!map_surrounded_by_walls(game))
		exit_game(game, 101, ERR_MAP_WALLS_MISSING, NULL);
	game->mlx = get_mlx_context(game->map);
	if (!game->mlx)
		exit_game(game, 102, ERR_CREATE_MLX_CONTEXT, NULL);
	err = parse_textures(game);
	if (err < 0)
		exit_game(game, ft_abs(err), ERR_TEXTURE_PARSE, get_config_error(&err));
	parse_sprites(game);
	game->cam.z_buffer = (double *)malloc(sizeof(double) * game->map->res_x);
	if (!game->cam.z_buffer)
		exit_game(game, 104, ERR_Z_BUFFER_ALLOC, NULL);
	if (save_bmp == 0 && create_win(game, argv[0]) < 0)
		exit_game(game, 106, ERR_CREATE_WIN, NULL);
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
