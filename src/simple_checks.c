/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 18:18:24 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/17 18:35:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	valid_color_struct(t_col_rgba *col)
{
	if (col->a > 255 || col->r > 255 || col->g > 255 || col->b > 255)
		return (0);
	return (1);
}

int	valid_color_string(char *s)
{
	int		comma_count;
	int		num_count;

	comma_count = 0;
	while (*s && comma_count < 3)
	{
		num_count = 0;
		while (*s && *s != ',')
		{
			if (num_count < 4 && ft_isdigit(*s))
				num_count++;
			else if (num_count > 3)
				return (0);
			else if (*s != ' ')
				return (0);
			s++;
		}
		if (*s == ',')
			comma_count++;
		if (*s)
			s++;
	}
	if (comma_count > 2)
		return (0);
	return (1);
}

int	valid_config_number(char *s, int space_stop)
{
	int		space_found;

	space_found = 0;
	while (*s && ((space_stop == 1 && space_found == 0) || space_stop == 0))
	{
		if (*s == ' ')
			space_found = 1;
		else if (ft_isdigit(*s))
		{
			if (space_found > 0)
				return (0);
		}
		else
			return (0);
		s++;
	}
	return (1);
}
