/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   c3d_render.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 15:44:29 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 15:52:57 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_RENDER_H
# define C3D_RENDER_H

# define COLOR_VALUE_UNDEFINED 0xAAFFFFFF

int					init_texture(t_tex **tex, char *file_path);
void				free_texture(void *mlx, t_tex *tex);
int					parse_textures(t_game *game);
void				parse_sprites(t_game *game);
void				render_sprites(t_game *game);
unsigned int		get_color(t_img *img, int x, int y);
int					parse_color_map(unsigned int *p, char **c);
t_mlx_ctx			*get_mlx_context(t_map *map);
int					create_win(t_game *game, char *win_title);
void				*free_mlx_context(t_mlx_ctx *ctx);
unsigned int		convert_endian(int from_endian, unsigned int c);
void				put_pixel(t_mlx_ctx *mlx, int x, int y, unsigned int color);
void				put_pixel_endian(t_mlx_ctx *mlx, t_coords *p,
						unsigned int c, int c_endian);
void				put_rect(t_mlx_ctx *mlx, t_rect *rect);
void				clear_img(t_mlx_ctx *mlx, t_map *map);
int					export_frame_as_bmp(t_game *game, char *file_name);
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
int					mouse_show_hide(t_game *game, int hidden);
int					move_mouse(t_game *game, int x, int y);
void				init_ray(t_game *game, t_render_holder_walls *hold);
void				init_drawer(t_game *game, t_render_holder_walls *hold);
void				init_texture_draw(t_game *game,
						t_render_holder_walls *hold);
void				init_sprite_render(t_game *game,
						t_render_holder_sprites *hold);

#endif
