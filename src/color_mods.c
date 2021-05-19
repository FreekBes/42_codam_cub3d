/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_mods.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 15:55:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 15:56:12 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// brighten and saturate a color by using bitwise operations
// could have used calculations here, but that turned out to be
// really slow really quickly, even for small resolutions

unsigned int	brighten(unsigned int color)
{
	unsigned int	saturate;

	saturate = ((color & 0x80808080) >> 7) * 255;
	return (((color & 0x7F7F7F7F) << 1) | saturate | 0x01010101);
}

unsigned int	darken(unsigned int color)
{
	return ((color >> 1) & 8355711);
}
