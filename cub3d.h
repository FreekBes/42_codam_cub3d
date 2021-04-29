/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/29 21:06:48 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifdef __linux__
#  include "lib/mlx_lin/mlx.h"
# else
#  include "lib/mlx/mlx.h"
# endif
# include "lib/libft/libft.h"
# include "os_specifics.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define CAM_MOV_SPEED_FORW_BACKW 0.03
# define CAM_MOV_SPEED_SIDEWAYS 0.025
# define CAM_SPRINT_SPEED_MOD 1.7
# define CAM_ROT_SPEED 0.06
# define CAM_MOUSE_SENSITIVITY 0.15

typedef struct s_map_node
{
	char			c;
	int				x;
	int				y;
}					t_map_node;

typedef struct s_keys_status
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				shift;
}					t_keys_status;

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

typedef struct s_tex
{
	char			*file_path;
	void			*img;
	int				*w;
	int				*h;
}					t_tex;

typedef struct s_map
{
	char			**lvl;
	size_t			lvl_w;
	size_t			lvl_h;
	unsigned int	res_x;
	unsigned int	res_y;
	t_tex			*tex_no;
	t_tex			*tex_so;
	t_tex			*tex_we;
	t_tex			*tex_ea;
	t_tex			*tex_sprite;
	unsigned int	col_floor;
	unsigned int	col_ceiling;
}					t_map;

typedef struct s_cam
{
	double			speed_mod;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
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
	t_keys_status	key_stat;
	t_mlx_ctx		*mlx;
	t_map			*map;
	t_cam			cam;
}					t_game;

int					print_error(char *msg);
void				print_color(t_col_rgba color);
void				print_map(t_map map, char **lvl);
t_tex				*init_texture(char *file_path);
void				free_texture(void *mlx, t_tex *tex);
int					parse_textures(t_game *game);
void				free_lvl(char **lvl, size_t lvl_h);
char				**lvl_copy(t_map *map);
void				free_map(void *mlx, t_map *map);
int					map_filename_valid(char *map_file);
int					map_characters_valid(t_map *map);
t_map				*parse_map(char *map_file);
int					set_starting_pos(t_game *game);
int					map_surrounded_by_walls(t_game *game);
t_mlx_ctx			*get_mlx_context(t_map *map, char *win_title);
void				*free_mlx_context(t_mlx_ctx *ctx);
unsigned int		color_to_uint(t_col_rgba *color);
t_col_rgba			uint_to_color(unsigned int color);
void				put_pixel(t_img *img, int x, int y, unsigned int color);
unsigned int		get_pixel(t_img *img, int x, int y);
void				put_rect(t_img *img, t_rect *rect);
void				put_vert_line(t_img *img, int x, int drawStart, int drawEnd, unsigned int color);
void				put_hori_line(t_img *img, int y, int drawStart, int drawEnd, unsigned int color);
void				clear_img(t_img *img, t_map *map);
int					export_frame_as_bmp(t_game *game, char *file_name);

#endif
