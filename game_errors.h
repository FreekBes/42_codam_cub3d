/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_errors.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 18:58:11 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/17 19:05:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ERRORS_H
# define GAME_ERRORS_H

# define ERR_MAP_MISSING "No config (.cub) file specified as first argument"
# define ERR_MAP_READ_PARSE "Failed to read or parse config (.cub) file"
# define ERR_START_POS "Start position in map is invalid or not set"
# define ERR_MAP_WALLS_MISSING "Map is not surrounded by walls"
# define ERR_CREATE_MLX_CONTEXT "Failed to create an MLX instance"
# define ERR_TEXTURE_PARSE "Failed to parse textures, do the files exist?"
# define ERR_Z_BUFFER_ALLOC "Could not allocate memory for z_buffer"
# define ERR_BMP_EXPORT "Failed to export first frame as BMP"

#endif
