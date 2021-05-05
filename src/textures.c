/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 20:47:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/05 20:31:02 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_tex	*init_texture(char *file_path)
{
	t_tex	*tex;

	tex = (t_tex *)malloc(sizeof(t_tex));
	if (tex)
	{
		tex->h = 0;
		tex->w = 0;
		tex->file_path = ft_strdup(file_path);
		tex->img.img_ptr = NULL;
	}
	return (tex);
}

unsigned int	get_color(t_tex *tex, int x, int y)
{
	char	*dst;

	dst = tex->img.address + y * tex->img.line_size;
	dst += x * (tex->img.bits_per_pixel / 8);
	return (*(unsigned int *)dst);
}

void	free_texture(void *mlx, t_tex *tex)
{
	if (tex->img.img_ptr)
		mlx_destroy_image(mlx, tex->img.img_ptr);
	free(tex->file_path);
	free(tex);
}

static int	parse_texture(void *mlx, t_tex *tex)
{
	tex->img.img_ptr = mlx_xpm_file_to_image(mlx, tex->file_path,
			&(tex->w), &(tex->h));
	if (tex->img.img_ptr == NULL)
		return (-1);
	tex->img.address = mlx_get_data_addr(tex->img.img_ptr,
			&(tex->img.bits_per_pixel), &(tex->img.line_size),
			&(tex->img.endian));
	return (1);
}

int	parse_textures(t_game *game)
{
	if (!(game->map->tex_no)
		|| parse_texture(game->mlx->core, game->map->tex_no) < 0)
		return (-1);
	if (!(game->map->tex_so)
		|| parse_texture(game->mlx->core, game->map->tex_so) < 0)
		return (-1);
	if (!(game->map->tex_we)
		|| parse_texture(game->mlx->core, game->map->tex_we) < 0)
		return (-1);
	if (!(game->map->tex_ea)
		|| parse_texture(game->mlx->core, game->map->tex_ea) < 0)
		return (-1);
	if (!(game->map->tex_sprite)
		|| parse_texture(game->mlx->core, game->map->tex_sprite) < 0)
		return (-1);
	return (1);
}
