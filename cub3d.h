/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/14 16:22:29 by fbes          ########   odam.nl         */
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
# include <math.h>

typedef struct s_col_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_col_rgba;

typedef struct s_rect
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	w;
	unsigned int	h;
	unsigned int	c;
}					t_rect;

typedef struct s_map
{
	char			**lvl;
	size_t			lvl_w;
	size_t			lvl_h;
	unsigned int	res_x;
	unsigned int	res_y;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	char			*tex_sprite;
	unsigned int	col_floor;
	unsigned int	col_ceiling;
}					t_map;

typedef struct s_cam
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
}					t_cam;

typedef struct s_img
{
	void			*img_ptr;
	char			*address;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
}					t_img;

typedef struct s_mlx_ctx
{
	void			*core;
	void			*win;
	t_img			*img;
}					t_mlx_ctx;

typedef struct s_game
{
	t_mlx_ctx		*mlx;
	t_map			*map;
	t_cam			cam;
}					t_game;

int					print_error(char *msg);
void				print_color(t_col_rgba color);
void				print_map(t_map map);
t_map				*parse_map(char *map_file);
t_mlx_ctx			*get_mlx_context(t_map *map, char *win_title);
void				*free_mlx_context(t_mlx_ctx *ctx);
unsigned int		color_to_uint(t_col_rgba *color);
void				put_pixel(t_img *img, int x, int y, unsigned int color);
void				put_rect(t_img *img, t_rect *rect);
void				put_vert_line(t_img *img, int x, int drawStart, int drawEnd, unsigned int color);
void				put_hori_line(t_img *img, int y, int drawStart, int drawEnd, unsigned int color);

#endif
