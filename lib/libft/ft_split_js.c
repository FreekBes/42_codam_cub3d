/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_js.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:41:13 by fbes          #+#    #+#                 */
/*   Updated: 2021/06/14 22:08:43 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_seps_amount(char *s, char c)
{
	size_t	amount;

	amount = 0;
	while (*s != '\0')
	{
		if (*s == c)
			amount++;
		s++;
	}
	return (amount);
}

void	copy_part(char **arr, char const *s, char c, size_t *j)
{
	size_t	len;

	len = ft_strclen(s, c);
	arr[*j] = ft_calloc(len + 1, sizeof(char));
	ft_memccpy(arr[*j], s, c, len);
	(*j)++;
}

char	**ft_split_js(char const *s, char c)
{
	char	**arr;
	size_t	seps_amount;
	size_t	i;
	size_t	j;

	seps_amount = get_seps_amount((char *)s, c);
	arr = (char **)malloc((seps_amount + 3) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (1)
	{
		if (i == 0)
			copy_part(arr, &s[i], c, &j);
		if (s[i] == c)
			copy_part(arr, &s[i + 1], c, &j);
		if (s[i] == '\0')
			break ;
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
