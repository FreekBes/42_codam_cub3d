/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 13:29:15 by fbes          #+#    #+#                 */
/*   Updated: 2021/05/19 15:27:57 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*get_config_error_basic(int *err)
{
	if (*err == -2)
		return (ft_strdup(ERR_CONF_EMPTY));
	else if (*err == -3)
		return (ft_strdup(ERR_CONF_RES_MT));
	else if (*err == -4)
		return (ft_strdup(ERR_CONF_FC));
	else if (*err == -5)
		return (ft_strdup(ERR_CONF_CC));
	else if (*err == -6)
		return (ft_strdup(ERR_OUT_OF_MEM));
	else if (*err == -7)
		return (ft_strdup(ERR_CONF_RES_INV));
	else if (*err == -8)
		return (ft_strdup(ERR_CONF_TEX_MT));
	else if (*err == -10)
		return (ft_strdup(ERR_CONF_C_MT));
	else if (*err == -11)
		return (ft_strdup(ERR_CONF_C_INV));
	return (ft_strdup(ERR_UNKNOWN));
}

static char	*get_config_error_tex(int *err)
{
	if (*err == -60)
		return (ft_strdup(ERR_XPM_PARSE));
	else if (*err == -61)
		return (ft_strdup(ERR_TEX_NO));
	else if (*err == -62)
		return (ft_strdup(ERR_TEX_SO));
	else if (*err == -63)
		return (ft_strdup(ERR_TEX_WE));
	else if (*err == -64)
		return (ft_strdup(ERR_TEX_EA));
	else if (*err == -65)
		return (ft_strdup(ERR_TEX_SPRITE));
	else if (*err == -66)
		return (ft_strdup(ERR_TEX_MISSING));
	else if (*err == -67)
		return (ft_strdup(ERR_TEX_EXT_INV));
	return (ft_strdup(ERR_UNKNOWN));
}

int	set_err(int *err, int n)
{
	*err = n;
	return (n);
}

char	*get_config_error(int *err)
{
	if (*err >= -11 && *err <= -2)
		return (get_config_error_basic(err));
	else if (*err >= -67 && *err <= -60)
		return (get_config_error_tex(err));
	else if (*err == -30)
		return (ft_strdup(ERR_CONF_EXT_INV));
	else if (*err == -31)
		return (ft_strdup(ERR_CONF_OPEN));
	else if (*err == -33)
		return (ft_strdup(ERR_CONF_READ));
	else if (*err == -40)
		return (ft_strdup(ERR_MAP_INVALID_CHAR));
	else if (*err == -41)
		return (ft_strdup(ERR_MAP_START_MT));
	else if (*err == -42)
		return (ft_strdup(ERR_MAP_MISSING));
	else if (*err == -43)
		return (ft_strdup(ERR_CONF_RES_MISSING));
	else if (*err == -44)
		return (ft_strdup(ERR_CONF_C_MISSING));
	else if (*err == -50)
		return (ft_strdup(ERR_BMP_CREATE));
	else if (*err == -51)
		return (ft_strdup(ERR_BMP_WRITE));
	return (ft_strdup(ERR_UNKNOWN));
}
