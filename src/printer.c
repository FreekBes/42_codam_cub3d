/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:31:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/07 18:10:02 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	print_error(char *msg)
{
	printf("Error\n%s\n", msg);
	strerror(errno);
	return (-1);
}

void	print_color(t_col_rgba color)
{
	printf("R%i, G%i, B%i, A%i\n", (int)color.r, (int)color.g,
		(int)color.b, (int)color.a);
}

void	print_sprite(void *sprite)
{
	t_sprite	*why;

	why = (t_sprite *)sprite;
	printf("sprite distance: %f\n", why->dist);
}

void	print_level(t_map map, char **lvl)
{
	int		i;
	int		j;

	i = 0;
	if (!lvl)
		lvl = map.lvl;
	while (i < map.lvl_h)
	{
		j = 0;
		while (j < map.lvl_w)
		{
			printf("%c", lvl[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_map(t_map map, char **lvl)
{
	printf("res_x: %i\nres_y: %i\n", (int)map.res_x, (int)map.res_y);
	printf("tex_no: %s\n", map.tex_no->file_path);
	printf("tex_so: %s\n", map.tex_so->file_path);
	printf("tex_we: %s\n", map.tex_we->file_path);
	printf("tex_ea: %s\n", map.tex_ea->file_path);
	printf("tex_sprite: %s\n", map.tex_sprite->file_path);
	printf("col_floor: 0x%X\n", map.col_floor);
	printf("col_ceiling: 0x%X\n", map.col_ceiling);
	printf("lvl_w: %d, lvl_h: %d\n", map.lvl_w, map.lvl_h);
	print_level(map, lvl);
}
