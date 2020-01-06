/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:56:25 by akharrou          #+#    #+#             */
/*   Updated: 2020/01/06 11:07:45 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         o_handler -- formatted octal base number conversion
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char	*
**         o_handler(t_format format, t_data arg);
**
**    PARAMETERS
**
**         t_format format     Structure containing information about how
**                             the argument must be formatted in the string.
**
**         t_data arg          Argument pulled off of the 'va_list'.
**
**    DESCRIPTION
**         Handles the '%o' specifier like the libc 'printf()' function.
**
**         Note: the flags and fields that apply to this specifier are
**         the following:
**
**             Flags: '-', '+', ' ', '0', '#'
**             Width: defined or '*'
**             Precision: defined or '*'
**             Length: 'hh', 'h', 'l', 'll', 'j', 'z', 't'
**
**    RETURN VALUES
**         If successful, returns a formatted string that follows the
**         specified format; otherwise NULL.
*/

#include "../ft_printf.h"

char			*o_handler(t_format format, t_data arg)
{
	intmax_t	temp;
	char		*intstr;

	if (format.length < L && format.length != NONE)
		temp = (format.length == HH) ? arg.uchar_ : arg.ushort_;
	else
		temp = (format.length == NONE) ? arg.uint_ : arg.uintmax_;
	intstr = ft_strdup("");
	if (!(format.precision == 0 && temp == 0 && !(format.flags & HASH)))
	{
		format.precision -= (format.flags & HASH && temp) ? 1 : 0;
		temp = (temp < 0) ? ~temp + 1 : temp;
		intstr = ft_strjoinfre(
			intstr, ft_utoa_base(temp, OCTAL_BASE, format.precision), 1, 1);
		format.width -= ft_strlen(intstr);
		format.width -= (format.flags & HASH && temp) ? 1 : 0;
	}
	if (format.width && format.pad == '0')
		intstr = apply_width(format, intstr);
	if (format.flags & HASH && temp)
		intstr = ft_strprepend(intstr, "0", 1, 0);
	if (format.width && format.pad != '0')
		intstr = apply_width(format, intstr);
	return (intstr);
}