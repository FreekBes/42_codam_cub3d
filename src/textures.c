/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 20:47:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 17:39:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
#include "MLX42/MLX42.h"

int	init_texture(t_tex **tex, char *file_path)
{
	if (!extension_valid(file_path, ".xpm42")
		&& !extension_valid(file_path, ".XPM42"))
		return (-67);
	if (*tex)
		return (-8);
	*tex = (t_tex *)malloc(sizeof(t_tex));
	if (tex)
	{
		(*tex)->file_path = ft_strdup(file_path);
		if (!(*tex)->file_path)
		{
			ft_free(*tex);
			return (-6);
		}
		(*tex)->xpm = NULL;
		return (0);
	}
	return (-6);
}

// get color at position x, y from a texture

unsigned int	get_color(t_mlx_texture *img, int x, int y)
{
	uint8_t	*dst;

	dst = img->pixels + y * img->width + x;
	return (*(unsigned int *)dst);
}

void	free_texture(t_tex *tex)
{
	free(tex->file_path);
	free(tex);
}

static int	parse_texture(t_tex *tex)
{
	tex->xpm = mlx_load_xpm42(tex->file_path);
	if (tex->xpm == NULL)
		return (-1);
	return (1);
}

int	parse_textures(t_game *game)
{
	if (!(game->map->tex_no)
		|| parse_texture(game->map->tex_no) < 0)
		return (-61);
	if (!(game->map->tex_so)
		|| parse_texture(game->map->tex_so) < 0)
		return (-62);
	if (!(game->map->tex_we)
		|| parse_texture(game->map->tex_we) < 0)
		return (-63);
	if (!(game->map->tex_ea)
		|| parse_texture(game->map->tex_ea) < 0)
		return (-64);
	if (!(game->map->tex_sprite)
		|| parse_texture(game->map->tex_sprite) < 0)
		return (-65);
	return (1);
}
