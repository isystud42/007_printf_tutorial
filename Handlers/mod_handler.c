/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:29:03 by idsy              #+#    #+#             */
/*   Updated: 2020/01/21 11:30:14 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         mod_handler -- formatted modulo character ('%') conversion
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char	*
**         mod_handler(t_format format, t_data arg);
**
**    PARAMETERS
**
**         t_format format     Structure containing information about how
**                             the argument must be formatted in the string.
**
**         t_data arg          Argument pulled off of the 'va_list'.
**
**    DESCRIPTION
**         Handles the '%%' specifier like the libc 'printf()' function.
**
**         Note: the flags and fields that apply to this specifier are
**         the following:
**
**             Flags: '-', '0'
**             Width: defined or '*'
**
**    RETURN VALUES
**         If successful, returns a formatted string that follows the
**         specified format; otherwise NULL.
*/

#include "../ft_printf.h"

char	*mod_handler(t_format format, t_data arg)
{
	arg.char_ = '%';
	return (c_handler(format, arg));
}
