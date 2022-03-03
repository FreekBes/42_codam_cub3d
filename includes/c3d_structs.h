/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   c3d_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 15:52:38 by fbes          #+#    #+#                 */
/*   Updated: 2022/03/03 16:37:48 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_STRUCTS_H
# define C3D_STRUCTS_H

# include "MLX42/MLX42.h"

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct s_dcoords
{
	double			x;
	double			y;
}					t_dcoords;

typedef struct s_dimensions
{
	int				w;
	int				h;
}					t_dimensions;

typedef struct s_col_rgba
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_col_rgba;

typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
	uint32_t		c;
}					t_rect;

typedef struct s_tex
{
	char			*file_path;
	xpm_t			*xpm;
}					t_tex;

typedef struct s_sprite
{
	t_tex			*tex;
	double			x;
	double			y;
	double			dist;
}					t_sprite;

typedef struct s_cam
{
	double			*z_buffer;
	double			speed_mod;
	double			mouse_sens;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_cam;

typedef struct s_mlx_ctx
{
	void			*core;
	mlx_image_t		*img;
}					t_mlx_ctx;

typedef struct s_render_holder_sprites
{
	t_sprite		*sprite;
	t_dcoords		sprite_pos;
	double			inv_det;
	t_dcoords		transform;
	int				sprite_screen_x;
	t_dimensions	sprite_dims;
	t_coords		draw_start;
	t_coords		draw_end;
	int				stripe;
	t_coords		tex_c;
	int				d;
	int				y;
	uint32_t		color;
}					t_render_holder_sprites;

typedef struct s_render_holder_walls
{
	t_tex			*tex;
	t_coords		pixel;
	double			cam_x;
	t_dcoords		ray_dir;
	t_coords		map;
	t_dcoords		side_dist;
	t_dcoords		delta_dist;
	double			perp_wall_dist;
	t_coords		step;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	uint32_t		color;
	double			wall_x;
	t_coords		tex_c;
	double			tex_pos;
	double			tex_step;
}					t_render_holder_walls;

typedef struct s_map
{
	char			**lvl;
	t_list			*sprites;
	int				lvl_w;
	int				lvl_h;
	int32_t			res_x;
	int32_t			res_y;
	t_tex			*tex_no;
	t_tex			*tex_so;
	t_tex			*tex_we;
	t_tex			*tex_ea;
	t_tex			*tex_sprite;
	uint32_t		col_floor;
	uint32_t		col_ceiling;
}					t_map;

typedef struct s_game
{
	t_mlx_ctx		*mlx;
	t_map			*map;
	t_cam			cam;
	int				bmp_export;
}					t_game;

#endif
