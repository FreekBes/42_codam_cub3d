/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 18:18:24 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

// check if a color structure contains no values over 255.
// originally, I had an unsigned char in place to make sure that this would
// never happen, but then it overflowed, which caused invalid RGB values
// to actually output colors. I found that a nice solution, but others may
// think otherwise, so now each value in the struct is an integer, which does
// take up more memory, but is able to hold invalid information given in the
// .cub config file as well, to let the user know there's an error in it.

int	valid_color_struct(t_col_rgba *col)
{
	if (col->a > 255 || col->r > 255 || col->g > 255 || col->b > 255)
		return (0);
	return (1);
}

// check if a string of colors only contains commas, whitespace and three
// digits between each comma and/or whitespace.

int	valid_color_string(char *s)
{
	int		comma_count;
	int		num_count;

	comma_count = 0;
	while (*s && comma_count < 3)
	{
		num_count = 0;
		while (*s && *s != ',' && num_count < 4)
		{
			if (ft_isdigit(*s))
				num_count++;
			else if (!ft_iswhitespace(*s))
				return (0);
			s++;
		}
		if (num_count > 3)
			return (0);
		if (*s == ',')
			comma_count++;
		if (*s)
			s++;
	}
	if (comma_count > 2)
		return (0);
	return (1);
}

// check if a numeric string contains just one number without a space
// in the middle, or up to the EOL character (if space_stop == 1).

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
