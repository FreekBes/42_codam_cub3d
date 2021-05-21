/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_mods.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 15:55:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/21 15:27:17 by fbes          ########   odam.nl         */
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

// convert between endians
// from_endian defines which endian is used for c
// if it is 1, it is big endian, if it is 0, it is little

unsigned int	convert_endian(int from_endian, unsigned int c)
{
	unsigned int	cc;

	if (from_endian == 1)
		cc = (c << 24) |((c << 8) & 0x00ff0000)
			| ((c >> 8) & 0x0000ff00) | (c >> 24);
	else
		cc = (c << 0) | (c << 8) | (c << 16) | (c << 24);
	return (cc);
}
