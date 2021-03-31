/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:31:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/31 16:55:32 by fbes          ########   odam.nl         */
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
	printf("R%i, G%i, B%i, A%i", (int)color.r, (int)color.g,
		(int)color.b, (int)color.a);
}

void	print_map(t_map map)
{
	printf("res_x: %i\nres_y: %i\n", (int)map.res_x, (int)map.res_y);
	printf("tex_no: %s\ntex_so: %s\n", map.tex_no, map.tex_so);
	printf("tex_we: %s\ntex_ea: %s\n", map.tex_we, map.tex_ea);
	printf("tex_sprite: %s\ncol_floor: 0x%X", map.tex_sprite, map.col_floor);
	printf("\ncol_ceiling: 0x%X\n", map.col_ceiling);
}
