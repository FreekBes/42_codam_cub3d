/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/21 15:09:17 by fbes          ########   odam.nl         */
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
# include "game_errors.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define COLOR_VALUE_UNDEFINED 0xAAFFFFFF
# define CAM_MOV_SPEED_FORW_BACKW 0.05
# define CAM_MOV_SPEED_SIDEWAYS 0.037
# define CAM_SPRINT_SPEED_MOD 1.7
# define CAM_ROT_SPEED 0.06
# define CAM_DEFAULT_MOUSE_SENSITIVITY 0.15

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
	unsigned int	c;
}					t_rect;

typedef struct s_img
{
	void			*img_ptr;
	char			*address;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
}					t_img;

typedef struct s_tex
{
	char			*file_path;
	t_img			img;
	int				w;
	int				h;
}					t_tex;

typedef struct s_sprite
{
	t_tex			*tex;
	double			x;
	double			y;
	double			dist;
}					t_sprite;

typedef struct s_map
{
	char			**lvl;
	t_list			*sprites;
	int				lvl_w;
	int				lvl_h;
	int				res_x;
	int				res_y;
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
	void			*win;
	t_img			img;
}					t_mlx_ctx;

typedef struct s_game
{
	t_keys_status	key_stat;
	t_mlx_ctx		*mlx;
	t_map			*map;
	t_cam			cam;
	int				bmp_export;
}					t_game;

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
	unsigned int	color;
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
	unsigned int	color;
	double			wall_x;
	t_coords		tex_c;
	double			tex_pos;
	double			tex_step;
}					t_render_holder_walls;

int					set_err(int *err, int n);
char				*get_config_error(int *err);
void				free_lines(char **lines);
void				item_free_simple(void *content);
char				*skip_spaces(char *c);
char				*skip_non_spaces(char *c);
t_coords			*new_coords(int x, int y);
int					print_error(char *msg);
void				print_color(t_col_rgba color);
void				print_sprite(void *sprite);
unsigned int		brighten(unsigned int color);
unsigned int		darken(unsigned int color);
void				print_map(t_map map, char **lvl);
int					init_texture(t_tex **tex, char *file_path);
void				free_texture(void *mlx, t_tex *tex);
int					parse_textures(t_game *game);
void				parse_sprites(t_game *game);
void				render_sprites(t_game *game);
unsigned int		get_color(t_tex *tex, int x, int y);
int					parse_color_map(unsigned int *p, char **c);
int					free_lvl(char **lvl, size_t lvl_h);
char				**lvl_copy(t_map *map);
t_map				*new_map(void);
void				*free_map(void *mlx, t_map *map);
int					extension_valid(char *file_name, char *ext);
int					map_characters_valid(t_map *map, int *err);
int					config_valid(t_map *map, int *err);
int					valid_config_number(char *s, int space_stop);
int					valid_color_string(char *s);
int					valid_color_struct(t_col_rgba *col);
int					parse_level(t_map **map, char *line);
t_map				*config_to_map(char **config, int *err);
t_map				*parse_map(char *map_file, int *err);
int					set_starting_pos(t_game *game);
int					map_surrounded_by_walls(t_game *game);
t_mlx_ctx			*get_mlx_context(t_map *map, char *win_title);
void				*free_mlx_context(t_mlx_ctx *ctx);
unsigned int		color_to_uint(t_col_rgba *color);
t_col_rgba			uint_to_color(unsigned int color);
unsigned int		convert_endian(int from_endian, unsigned int c);
void				put_pixel(t_img *img, int x, int y, unsigned int color);
void				put_pixel_endian(t_img *img, t_coords *p,
						unsigned int c, int c_endian);
unsigned int		get_pixel(t_img *img, int x, int y);
void				put_rect(t_img *img, t_rect *rect);
void				clear_img(t_img *img, t_map *map);
int					export_frame_as_bmp(t_game *game, char *file_name);
t_map_node			*new_map_node(int x, int y, char c);
int					clear_queue(t_list *queue, char **temp_lvl, size_t lvl_h);
int					inside(char **temp_lvl, int x, int y);
int					outside(t_game *game, char **temp_lvl, int x, int y);
void				move_cam(t_game *game, double dir_fb, double dir_side);
void				rotate_cam(t_game *game, double dir);
void				render_walls(t_game *game);
void				render_next_frame(t_game *game);
int					draw_next_frame(t_game *game);
int					win_focus(t_game *game);
int					mousemove(int x, int y, t_game *game);
int					mousebtnpress(int btncode, int x, int y, t_game *game);
int					keyrelease(int keycode, t_game *game);
int					keypress(int keycode, t_game *game);
void				handle_key_presses(t_game *game);
void				reset_key_presses(t_keys_status *key_status);
int					mouse_show_hide(t_game *game, int hidden);
int					move_mouse(t_game *game, int x, int y);
void				init_ray(t_game *game, t_render_holder_walls *hold);
void				init_drawer(t_game *game, t_render_holder_walls *hold);
void				init_texture_draw(t_game *game,
						t_render_holder_walls *hold);
void				init_sprite_render(t_game *game,
						t_render_holder_sprites *hold);
int					exit_game(t_game *game, int exit_code,
						char *error_msg, char *m_error_msg);

#endif
