/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   c3d_os_specifics.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/15 19:50:02 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/27 16:01:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_OS_SPECIFICS_H
# define C3D_OS_SPECIFICS_H
# ifdef __linux__
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_ESC 65307
#  define KEY_LSHIFT 65505
#  define KEY_RSHIFT 65506
#  define BTN_SCROLL_UP 4
#  define BTN_SCROLL_DOWN 5
# else
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_ESC 53
#  define KEY_LSHIFT 257
#  define KEY_RSHIFT 258
#  define BTN_SCROLL_UP 4
#  define BTN_SCROLL_DOWN 5
# endif
#endif
