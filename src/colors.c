/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 15:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/31 16:05:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// the << operator below is a bite shift operator.
// 11100101 << 1 would produce 11001010, as all bits
// are shifted to the left by 1 bit. The blank spaces
// at the end are filled by zeroes.
// see https://en.wikipedia.org/wiki/Bitwise_operations_in_C

unsigned int	color_to_uint(t_col_rgba color)
{
	unsigned int	ucol;

	ucol = (color.a << 24) + (color.r << 16) + (color.g << 8) + color.b;
	return (ucol);
}
