/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 15:58:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/07 17:10:10 by fbes          ########   odam.nl         */
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
	while (item->next)
	{
		sprite = (t_sprite *)(item->content);
		sprite->dist = ((p_x - sprite->x) * (p_x - sprite->x)
			+ (p_y - sprite->y) * (p_y - sprite->y));
		item = item->next;
	}
}

static int	compare_sprite_distances(void *s1, void *s2)
{
	return (((t_sprite *)s1)->dist > ((t_sprite *)s2)->dist);
}

void	render_sprites(t_game *game)
{
	if (game->map->sprites != NULL)
	{
		calc_distances(game);
		ft_lstsort(&game->map->sprites, &compare_sprite_distances);
		mlx_do_sync(game->mlx->core);
		printf("First sprite position: %f, %f\n", ((t_sprite *)(game->map->sprites->content))->x, ((t_sprite *)(game->map->sprites->content))->y);
	}
}
