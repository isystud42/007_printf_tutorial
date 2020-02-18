/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:26:42 by idsy              #+#    #+#             */
/*   Updated: 2020/02/13 18:26:44 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         s_handler -- formatted string conversion
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char	*
**         s_handler(t_format format, t_data arg);
**
**    PARAMETERS
**
**         t_format format     Structure containing information about how
**                             the argument must be formatted in the string.
**
**         t_data arg          Argument pulled off of the 'va_list'.
**
**    DESCRIPTION
**         Handles the '%s' specifier like the libc 'printf()' function.
**
**         Note: the flags and fields that apply to this specifier are
**         the following:
**
**             Flags: '-'
**             Width: defined or '*'
**             Precision: defined or '*'
**
**    RETURN VALUES
**         If successful, returns a formatted string that follows the
**         specified format; otherwise NULL.
*/

#include "../ft_printf.h"

char			*s_handler(t_format format, t_data arg)
{
	char		*fstr;

	fstr = (arg.str_ == NULL) ?
		ft_strdup("(null)") :
		ft_strdup(arg.str_);
	if (format.precision != NONE)
		if (0 <= format.precision && format.precision < (long)ft_strlen(fstr))
			fstr[format.precision] = '\0';
	format.width -= ft_strlen(fstr);
	if (format.width > 0 && format.pad == ' ')
		fstr = apply_width(format, fstr);
	return (fstr);
}
