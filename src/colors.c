/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

// the << operator below is a bite shift operator.
// 11100101 << 1 would produce 11001010, as all bits
// are shifted to the left by 1 bit. The blank spaces
// at the end are filled by zeroes. The | is an OR operator.
// see https://en.wikipedia.org/wiki/Bitwise_operations_in_C
// all unsigned ints returned here are stored in little-endian format.

unsigned int	color_to_uint(t_col_rgba *color)
{
	return (color->a << 24 | color->r << 16 | color->g << 8 | color->b);
}

t_col_rgba	uint_to_color(unsigned int color)
{
	t_col_rgba	tcol;

	tcol.a = 0xFF & (color >> 24);
	tcol.r = 0xFF & (color >> 16);
	tcol.g = 0xFF & (color >> 8);
	tcol.b = 0xFF & (color);
	return (tcol);
}

static int	parse_color_check(char **c)
{
	if (!*c)
		return (0);
	*c = skip_spaces(*c + 1);
	if (!ft_isdigit(**c))
		return (0);
	return (1);
}

int	parse_color_map(unsigned int *p, char **c)
{
	t_col_rgba		t_col;

	if (*p != COLOR_VALUE_UNDEFINED)
		return (-10);
	if (!valid_color_string(*c) || !ft_isdigit(**c))
		return (-11);
	t_col.r = ft_atoi(*c);
	*c = ft_strchr(*c, ',');
	if (!parse_color_check(c))
		return (-11);
	t_col.g = ft_atoi(*c);
	*c = ft_strchr(*c, ',');
	if (!parse_color_check(c))
		return (-11);
	t_col.b = ft_atoi(*c);
	t_col.a = 0;
	if (valid_color_struct(&t_col))
		*p = color_to_uint(&t_col);
	else
		return (-11);
	return (0);
}
