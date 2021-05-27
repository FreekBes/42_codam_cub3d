/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 15:58:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static t_sprite	*new_sprite(t_game *game, t_tex *tex, t_coords *pos, int do_add)
{
	t_sprite	*sprite;
	t_list		*item;

	if (!pos)
		return (NULL);
	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite)
	{
		sprite->x = pos->x + 0.5;
		sprite->y = pos->y + 0.5;
		sprite->tex = tex;
		if (do_add == 1)
		{
			item = ft_lstnew(sprite);
			if (item)
				ft_lstadd_back(&game->map->sprites, item);
			else
				sprite = ft_free((void *)sprite);
		}
	}
	if (pos)
		ft_free(pos);
	return (sprite);
}

void	parse_sprites(t_game *game)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map->lvl_h)
	{
		j = 0;
		while (j < game->map->lvl_w)
		{
			if (game->map->lvl[i][j] == '2')
				new_sprite(game, game->map->tex_sprite, new_coords(i, j), 1);
			j++;
		}
		i++;
	}
}
