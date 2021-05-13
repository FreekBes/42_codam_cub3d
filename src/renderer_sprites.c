/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_sprites.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 19:54:55 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/13 20:08:39 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void	init_sprite_render(t_game *game, t_render_holder_sprites *hold)
{
	hold->sprite_pos.x = hold->sprite->x - game->cam.pos_x;
	hold->sprite_pos.y = hold->sprite->y - game->cam.pos_y;
	hold->inv_det = 1.0 / (game->cam.plane_x * game->cam.dir_y
			- game->cam.dir_x * game->cam.plane_y);
	hold->transform.x = hold->inv_det * (game->cam.dir_y * hold->sprite_pos.x
			- game->cam.dir_x * hold->sprite_pos.y);
	hold->transform.y = hold->inv_det * (-game->cam.plane_y
			* hold->sprite_pos.x + game->cam.plane_x * hold->sprite_pos.y);
	hold->sprite_screen_x = (1 + hold->transform.x / hold->transform.y)
		* (int)(game->map->res_x / 2);
	hold->sprite_dims.h = abs((int)(game->map->res_y / hold->transform.y));
	hold->draw_start.y = -hold->sprite_dims.h / 2 + game->map->res_y / 2;
	if (hold->draw_start.y < 0)
		hold->draw_start.y = 0;
	hold->draw_end.y = hold->sprite_dims.h / 2 + game->map->res_y / 2;
	if (hold->draw_end.y >= (int)(game->map->res_y))
		hold->draw_end.y = game->map->res_y - 1;
	hold->sprite_dims.w = abs((int)(game->map->res_y / hold->transform.y));
	hold->draw_start.x = -hold->sprite_dims.w / 2 + hold->sprite_screen_x;
	if (hold->draw_start.x < 0)
		hold->draw_start.x = 0;
	hold->draw_end.x = hold->sprite_dims.w / 2 + hold->sprite_screen_x;
	if (hold->draw_end.x >= (int)(game->map->res_x))
		hold->draw_end.x = game->map->res_x - 1;
	hold->stripe = hold->draw_start.x;
}

static void	render_sprite(t_game *game, t_render_holder_sprites *h)
{
	while (h->stripe < h->draw_end.x)
	{
		h->tex.x = (int)(256 * (h->stripe - (-h->sprite_dims.w / 2
						+ h->sprite_screen_x)) * h->sprite->tex->w
				/ h->sprite_dims.w) / 256;
		if (h->transform.y > 0 && h->stripe > 0
			&& h->stripe < (int)(game->map->res_x)
			&& h->transform.y < game->cam.z_buffer[h->stripe])
		{
			h->y = h->draw_start.y;
			while (h->y < h->draw_end.y)
			{
				h->d = h->y * 256 - game->map->res_y * 128
					+ h->sprite_dims.h * 128;
				h->tex.y = ((h->d * h->sprite->tex->h)
						/ h->sprite_dims.h) / 256;
				h->color = get_color(h->sprite->tex, h->tex.x, h->tex.y);
				if ((h->color & 0x00FFFFFF) != 0)
					put_pixel(&game->mlx->img, h->stripe, h->y, h->color);
				h->y++;
			}
		}
		h->stripe++;
	}
}

void	render_sprites(t_game *game)
{
	t_list					*item;
	t_render_holder_sprites	hold;

	if (game->map->sprites != NULL)
	{
		calc_distances(game);
		ft_lstsort(&game->map->sprites, &compare_sprite_distances);
		item = game->map->sprites;
		while (item)
		{
			mlx_do_sync(game->mlx->core);
			hold.sprite = (t_sprite *)item->content;
			init_sprite_render(game, &hold);
			render_sprite(game, &hold);
			item = item->next;
		}
	}
}
