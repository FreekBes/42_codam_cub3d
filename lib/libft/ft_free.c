/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 19:45:17 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/31 19:48:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(void *freeable)
{
	if (freeable)
		free(freeable);
	return (NULL);
}
