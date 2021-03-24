/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/24 18:42:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "lib/libft/libft.h"
# include "lib/mlx/mlx.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_col_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_col_rgba;

typedef struct s_map
{
	unsigned int	res_x;
	unsigned int	res_y;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	char			*tex_sprite;
	t_col_rgba		*col_floor;
	t_col_rgba		*col_ceiling;
}					t_map;

t_map				*parse_map(char *map_file);

#endif
