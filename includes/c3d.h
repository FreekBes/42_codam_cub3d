/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   c3d.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:50:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 17:45:42 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_H
# define C3D_H
# include <stdlib.h>
# include "libft.h"
# include "c3d_structs.h"
# include "c3d_render.h"

# define CAM_MOV_SPEED_FORW_BACKW 0.05
# define CAM_MOV_SPEED_SIDEWAYS 0.037
# define CAM_SPRINT_SPEED_MOD 1.7
# define CAM_ROT_SPEED 0.06
# define CAM_DEFAULT_MOUSE_SENSITIVITY 0.15

void				init_game(t_game *game);
void				setup_args(int argc, char **argv, t_game *game);
void				setup_game(t_game *game, char **argv);
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
void				handle_key_presses(t_game *game);
int					free_lvl(char **lvl, int lvl_h);
char				**lvl_copy(t_map *map);
t_map				*new_map(void);
void				*free_map(t_map *map);
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
unsigned int		color_to_uint(t_col_rgba *color);
t_col_rgba			uint_to_color(unsigned int color);
int					inside(char **temp_lvl, int x, int y);
int					outside(t_game *game, char **temp_lvl, int x, int y);
int					exit_game(t_game *game, int exit_code,
						char *error_msg, char *m_error_msg);

#endif
