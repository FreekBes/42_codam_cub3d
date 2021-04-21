/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   os_specifics.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/15 19:50:02 by fbes          #+#    #+#                 */
/*   Updated: 2021/04/21 16:43:04 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OS_SPECIFICS_H
# define OS_SPECIFICS_H
#ifdef __linux__
# define OS_MLX_REQ_PARAMS game->mlx->core, game->mlx->win
# define OS_MLX_REQ_PARAMS_MOUSE_SHOW_HIDE game->mlx->core, game->mlx->win
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_ESC 65307
# define KEY_LSHIFT 65505
# define KEY_RSHIFT 65506
#else
# define OS_MLX_REQ_PARAMS game->mlx->win
# define OS_MLX_REQ_PARAMS_MOUSE_SHOW_HIDE
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53
# define KEY_LSHIFT 257
# define KEY_RSHIFT 258
#endif
#endif
