/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:26:38 by idsy              #+#    #+#             */
/*   Updated: 2020/02/11 14:51:02 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         u_handler -- formatted unsigned number conversion
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char	*
**         u_handler(t_format format, t_data arg);
**
**    PARAMETERS
**
**         t_format format     Structure containing the variable
**                             and information about how it must
**                             be formatted.
**
**         t_data arg          Argument taken from the 'va_list'.
**
**    DESCRIPTION
**         Handles the '%u' specifier like the libc 'printf()' function.
**
**         Note: the flags and fields that apply to this specifier are
**         the following:
**
**             Flags: '-', '0'
**             Width: defined or '*'
**             Precision: defined or '*'
**             Length: 'hh', 'h', 'l', 'll', 'j', 'z', 't'
**
**    RETURN VALUES
**         If successful, returns a formatted string that follows the
**         specified format; otherwise NULL.
*/

#include "../ft_printf.h"

char			*u_handler(t_format format, t_data arg)
{
	uintmax_t	temp;
	char		*intstr;

	temp = (format.length < L && format.length != NONE) ?
		arg.uint_ :
		arg.uintmax_;
	intstr = ft_strdup("");
	if (!(format.precision == 0 && temp == 0))
	{
		intstr = ft_strjoinfre(
			intstr, ft_utoa_base(temp, DECIMAL_BASE, format.precision), 1, 1);
		format.width -= ft_strlen(intstr);
	}
	if (format.width)
		intstr = apply_width(format, intstr);
	return (intstr);
}
