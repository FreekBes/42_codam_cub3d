/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_errors.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 18:58:11 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/26 19:47:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ERRORS_H
# define GAME_ERRORS_H

# define ERR_CONF_MISSING "No config (.cub) file specified as first argument"
# define ERR_CONF_READ_PARSE "Failed to read or parse config (.cub) file"
# define ERR_START_POS "Start position in map is invalid or not set"
# define ERR_MAP_WALLS_MISSING "Map is not surrounded by walls"
# define ERR_CREATE_MLX_CONTEXT "Failed to create an MLX instance"
# define ERR_CREATE_WIN "Failed to open an MLX window"
# define ERR_TEXTURE_PARSE "Failed to parse textures, do the files exist?"
# define ERR_Z_BUFFER_ALLOC "Could not allocate memory for z_buffer"
# define ERR_BMP_EXPORT "Failed to export first frame as BMP"
# define ERR_CONF_TEX_MT "Texture configuration set multiple times"
# define ERR_CONF_EMPTY "Invalid line in config file found"
# define ERR_CONF_RES_MT "Window resolution configuration set multiple times"
# define ERR_CONF_FC "Could not parse floor color, it might be invalid"
# define ERR_CONF_CC "Could not parse ceiling color, it might be invalid"
# define ERR_OUT_OF_MEM "Out of memory"
# define ERR_CONF_RES_INV "Invalid resolution set in config file"
# define ERR_CONF_RES_MISSING "Resolution not set in config file"
# define ERR_CONF_C_MT "Floor or ceiling color is set multiple times"
# define ERR_CONF_C_INV "Invalid color set for floor or ceiling"
# define ERR_CONF_EXT_INV "Invalid extension for config file, should be .cub"
# define ERR_CONF_OPEN "Could not open config file"
# define ERR_CONF_READ "An error occurred while reading config file"
# define ERR_MAP_INVALID_CHAR "Invalid character found in map"
# define ERR_MAP_START_MT "Start position set multiple times in map"
# define ERR_MAP_MISSING "Map missing in config file"
# define ERR_CONF_C_MISSING "Floor or ceiling color not set in config file"
# define ERR_BMP_CREATE "Failed to create BMP file for export"
# define ERR_BMP_WRITE "Failed to write to BMP file for export"
# define ERR_XPM_PARSE "Failed to parse XPM texture file"
# define ERR_TEX_NO "Failed to parse NO texture"
# define ERR_TEX_SO "Failed to parse SO texture"
# define ERR_TEX_WE "Failed to parse WE texture"
# define ERR_TEX_EA "Failed to parse EA texture"
# define ERR_TEX_SPRITE "Failed to parse sprite texture"
# define ERR_TEX_MISSING "One or more texture(s) is not defined in config file"
# define ERR_TEX_EXT_INV "Invalid extension for texture file, should be .xpm"
# define ERR_INVALID_ARG "Invalid argument"
# define ERR_UNKNOWN "An unknown error occurred"

#endif
