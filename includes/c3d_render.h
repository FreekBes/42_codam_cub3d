/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   c3d_render.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 15:44:29 by fbes          #+#    #+#                 */
/*   Updated: 2022/03/03 16:38:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_RENDER_H
# define C3D_RENDER_H

# define COLOR_VALUE_UNDEFINED 0xAAFFFFFF

int					init_texture(t_tex **tex, char *file_path);
void				free_texture(t_tex *tex);
int					parse_textures(t_game *game);
void				parse_sprites(t_game *game);
void				render_sprites(t_game *game);
uint32_t			get_color(mlx_texture_t *img, int x, int y);
int					parse_color_map(uint32_t *p, char **c);
t_mlx_ctx			*get_mlx_context(t_map *map, char *win_title);
void				*free_mlx_context(t_mlx_ctx *ctx);
uint32_t			convert_endian(int from_endian, uint32_t c);
void				put_pixel(t_mlx_ctx *mlx, int x, int y, uint32_t color);
void				put_rect(t_mlx_ctx *mlx, t_rect *rect);
void				move_cam(t_game *game, double dir_fb, double dir_side);
void				rotate_cam(t_game *game, double dir);
void				render_walls(t_game *game);
void				render_next_frame(t_game *game);
void				draw_next_frame(void *game);
int					win_focus(t_game *game);
void				check_mouse_movement(t_game *game);
void				mousescrollwheel(double xdelta, double ydelta, void *game);
void				win_resize(int32_t w, int32_t h, void *game);
void				init_ray(t_game *game, t_render_holder_walls *hold);
void				init_drawer(t_game *game, t_render_holder_walls *hold);
void				init_texture_draw(t_game *game,
						t_render_holder_walls *hold);
void				init_sprite_render(t_game *game,
						t_render_holder_sprites *hold);

#endif
