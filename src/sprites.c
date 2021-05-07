/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 15:58:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/07 18:22:55 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_sprite	*new_sprite(t_tex *tex, int x, int y)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite)
	{
		sprite->x = x + 0.5;
		sprite->y = y + 0.5;
		sprite->tex = tex;
	}
	return (sprite);
}

void	parse_sprites(t_game *game)
{
	t_list		*item;
	t_sprite	*sprite;
	int			i;
	int			j;

	i = 0;
	while (i < game->map->lvl_h)
	{
		j = 0;
		while (j < game->map->lvl_w)
		{
			if (game->map->lvl[i][j] == '2')
			{
				sprite = new_sprite(game->map->tex_sprite, i, j);
				if (sprite)
				{
					item = ft_lstnew(sprite);
					if (item)
						ft_lstadd_back(&game->map->sprites, item);
					else
						sprite = ft_free((void *)sprite);
				}
			}
			j++;
		}
		i++;
	}
}

static void	calc_distances(t_game *game)
{
	t_list		*item;
	t_sprite	*sprite;
	double		p_x;
	double		p_y;

	p_x = game->cam.pos_x;
	p_y = game->cam.pos_y;
	item = game->map->sprites;
	while (item)
	{
		sprite = (t_sprite *)(item->content);
		sprite->dist = ((p_x - sprite->x) * (p_x - sprite->x)
			+ (p_y - sprite->y) * (p_y - sprite->y));
		item = item->next;
	}
}

static int	compare_sprite_distances(void *s1, void *s2)
{
	return (((t_sprite *)s1)->dist < ((t_sprite *)s2)->dist);
}

void	render_sprites(t_game *game)
{
	t_list			*item;
	t_sprite		*sprite;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				d;
	int				tex_x;
	int				tex_y;
	int				y;
	unsigned int	color;
	if (game->map->sprites != NULL)
	{
		calc_distances(game);
		ft_lstsort(&game->map->sprites, &compare_sprite_distances);
		item = game->map->sprites;
		while (item)
		{
			sprite = (t_sprite *)item->content;
			sprite_x = sprite->x - game->cam.pos_x;
			sprite_y = sprite->y - game->cam.pos_y;
			inv_det = 1.0 / (game->cam.plane_x * game->cam.dir_y - game->cam.dir_x * game->cam.plane_y);
			transform_x = inv_det * (game->cam.dir_y * sprite_x - game->cam.dir_x * sprite_y);
			transform_y = inv_det * (-game->cam.plane_y * sprite_x + game->cam.plane_x * sprite_y);
			sprite_screen_x = (int)(game->map->res_x / 2) * (1 + transform_x / transform_y);
			sprite_height = abs((int)(game->map->res_y / transform_y));
			draw_start_y = -sprite_height / 2 + game->map->res_y / 2;
			if (draw_start_y < 0)
				draw_start_y = 0;
			draw_end_y = sprite_height / 2 + game->map->res_y / 2;
			if (draw_end_y >= (int)(game->map->res_y))
				draw_end_y = game->map->res_y - 1;
			sprite_width = abs((int)(game->map->res_y / transform_y));
			draw_start_x = -sprite_width / 2 + sprite_screen_x;
			if (draw_start_x < 0)
				draw_start_x = 0;
			draw_end_x = sprite_width / 2 + sprite_screen_x;
			if (draw_end_x >= (int)(game->map->res_x))
				draw_end_x = game->map->res_x - 1;
			stripe = draw_start_x;
			while (stripe < draw_end_x)
			{
				tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * sprite->tex->w / sprite_width) / 256;
				if (transform_y > 0 && stripe > 0 && stripe < (int)(game->map->res_x) && transform_y < game->cam.z_buffer[stripe])
				{
					y = draw_start_y;
					while (y < draw_end_y)
					{
						d = y * 256 - game->map->res_y * 128 + sprite_height * 128;
						tex_y = ((d * sprite->tex->h) / sprite_height) / 256;
						color = get_color(sprite->tex, tex_x, tex_y);
						if ((color & 0x00FFFFFF) != 0)
							put_pixel(&game->mlx->img, stripe, y, color);
						y++;
					}
				}
				stripe++;
			}
			item = item->next;
		}
		mlx_do_sync(game->mlx->core);
	}
}
