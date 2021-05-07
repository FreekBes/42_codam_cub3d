/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 16:41:18 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/07 17:26:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_lst_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	ft_lstsort(t_list **lst, int (*f)(void *, void *))
{
	size_t	size;
	t_list	*item;
	t_list	*item2;
	size_t	i;
	size_t	j;

	size = ft_lstsize(*lst);
	item = *lst;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		item2 = item;
		while (j < size - i - 1)
		{
			if ((*f)(item2->content, item2->next->content))
			{
				swap_lst_content(item, item2->next);
			}
			item2 = item2->next;
			j++;
		}
		i++;
		item = item->next;
	}
}
