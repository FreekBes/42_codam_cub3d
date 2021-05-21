/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 20:47:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/21 15:45:14 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_texture(t_tex **tex, char *file_path)
{
	if (!extension_valid(file_path, ".xpm")
		&& !extension_valid(file_path, ".XPM"))
		return (-67);
	if (*tex)
		return (-8);
	*tex = (t_tex *)malloc(sizeof(t_tex));
	if (tex)
	{
		(*tex)->h = 0;
		(*tex)->w = 0;
		(*tex)->file_path = ft_strdup(file_path);
		if (!(*tex)->file_path)
		{
			ft_free(*tex);
			return (-6);
		}
		(*tex)->img.img_ptr = NULL;
		return (0);
	}
	return (-6);
}

// get color at position x, y from a texture

unsigned int	get_color(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->address + y * img->line_size + x * (img->bits_per_pixel / 8);
	return (*(unsigned int *)dst);
}

void	free_texture(void *mlx, t_tex *tex)
{
	if (mlx && tex->img.img_ptr)
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
		return (-61);
	if (!(game->map->tex_so)
		|| parse_texture(game->mlx->core, game->map->tex_so) < 0)
		return (-62);
	if (!(game->map->tex_we)
		|| parse_texture(game->mlx->core, game->map->tex_we) < 0)
		return (-63);
	if (!(game->map->tex_ea)
		|| parse_texture(game->mlx->core, game->map->tex_ea) < 0)
		return (-64);
	if (!(game->map->tex_sprite)
		|| parse_texture(game->mlx->core, game->map->tex_sprite) < 0)
		return (-65);
	return (1);
}
