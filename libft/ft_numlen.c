/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 19:31:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/11 02:54:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_numlen(unsigned long long int n, unsigned int base)
{
	if (n < base)
		return (1);
	return (1 + ft_numlen(n / base, base));
}
