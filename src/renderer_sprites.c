/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_sprites.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 19:54:55 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/28 19:30:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"
	#include <stdio.h>

// calculate the distance between each sprite and the player

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

// render a single sprite
// always call init_sprite_render with the holder before calling this one!

static void	render_sprite(t_game *game, t_render_holder_sprites *h)
{
	while (h->stripe < h->draw_end.x)
	{
		h->tex_c.x = (int)(256 * (h->stripe - (-h->sprite_dims.w / 2
						+ h->sprite_screen_x)) * h->sprite->tex->xpm->texture.width
				/ h->sprite_dims.w) / 256;
		if (h->transform.y > 0 && h->stripe >= 0
			&& h->stripe < (int)(game->map->res_x)
			&& h->transform.y < game->cam.z_buffer[h->stripe])
		{
			h->y = h->draw_start.y;
			while (h->y < h->draw_end.y)
			{
				h->d = h->y * 256 - game->map->res_y * 128
					+ h->sprite_dims.h * 128;
				h->tex_c.y = ((h->d * h->sprite->tex->xpm->texture.height)
						/ h->sprite_dims.h) / 256;
				h->color = get_color(&h->sprite->tex->xpm->texture,
						h->tex_c.x, h->tex_c.y);
				if ((h->color & 0x00FFFFFF) != 0)
					mlx_putpixel(game->mlx->img, h->stripe, h->y, h->color);
				h->y++;
			}
		}
		h->stripe++;
	}
}

// below method is used as the compare method in ft_lstsort

static int	compare_sprite_distances(void *s1, void *s2)
{
	return (((t_sprite *)s1)->dist < ((t_sprite *)s2)->dist);
}

// render sprites to the image.
// first, calculate the distance between the player and each sprite.
// then, sort the list of sprites, so that the one that's the furthest away
// is the first in the list, which will then get drawn first, so that
// sprites nearer to the player overwrite the ones further away.

void	render_sprites(t_game *game)
{
	static t_render_holder_sprites	hold;
	t_list							*item;

	if (game->map->sprites != NULL)
	{
		calc_distances(game);
		ft_lstsort(&game->map->sprites, &compare_sprite_distances);
		item = game->map->sprites;
		while (item)
		{
			hold.sprite = (t_sprite *)item->content;
			init_sprite_render(game, &hold);
			render_sprite(game, &hold);
			item = item->next;
		}
	}
}
