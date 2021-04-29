/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 20:47:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/29 21:19:44 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_tex	*init_texture(char *file_path)
{
	t_tex	*tex;

	tex = (t_tex *)malloc(sizeof(t_tex));
	if (tex)
	{
		tex->img = NULL;
		tex->h = 0;
		tex->w = 0;
		tex->file_path = ft_strdup(file_path);
	}
	return (tex);
}

void	free_texture(void *mlx, t_tex *tex)
{
	if (tex->img)
		mlx_destroy_image(mlx, tex->img);
	free(tex->file_path);
	free(tex);
}

static int	parse_texture(void *mlx, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, tex->file_path, tex->w, tex->h);
	if (tex->img == NULL)
		return (-1);
	return (1);
}

int	parse_textures(t_game *game)
{
	if (!(game->map->tex_no) || parse_texture(game->mlx->core, game->map->tex_no) < 0)
		return (-1);
	if (!(game->map->tex_so) || parse_texture(game->mlx->core, game->map->tex_so) < 0)
		return (-1);
	if (!(game->map->tex_we) || parse_texture(game->mlx->core, game->map->tex_we) < 0)
		return (-1);
	if (!(game->map->tex_ea) || parse_texture(game->mlx->core, game->map->tex_ea) < 0)
		return (-1);
	if (!(game->map->tex_sprite) || parse_texture(game->mlx->core, game->map->tex_sprite) < 0)
		return (-1);
	return (1);
}
