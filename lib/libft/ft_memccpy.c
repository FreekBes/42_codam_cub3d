/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:31:33 by fbes          #+#    #+#                 */
/*   Updated: 2020/10/27 14:46:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dest_cpy;
	const char	*src_cpy;

	dest_cpy = dest;
	src_cpy = src;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		if (*src_cpy == (char)c)
			return ((void *)dest_cpy);
		src_cpy++;
		n--;
	}
	return (NULL);
}
