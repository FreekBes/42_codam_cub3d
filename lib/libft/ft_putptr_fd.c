/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putptr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 18:37:56 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/03 18:22:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ptr_loop(intptr_t ptr, int fd)
{
	static char	base[] = "0123456789abcdef";
	int			written_chars;

	written_chars = 0;
	if (ptr != 0)
	{
		written_chars = ptr_loop(ptr / 16, fd);
		write(fd, &base[ptr % 16], 1);
		return (written_chars + 1);
	}
	return (written_chars);
}

int	ft_putptr_fd(intptr_t ptr, int fd)
{
	write(fd, "0x", 2);
	if (ptr == 0)
	{
		write(fd, "0", 1);
		return (3);
	}
	return (2 + ptr_loop(ptr, fd));
}
