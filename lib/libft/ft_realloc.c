/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 18:12:09 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/07 18:24:59 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		new_size = 1;
	if (ptr)
		free(ptr);
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		ft_memmove(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}
