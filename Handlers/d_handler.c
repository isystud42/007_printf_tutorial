/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:26:56 by idsy              #+#    #+#             */
/*   Updated: 2020/02/13 18:26:58 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         d_handler -- formatted decimal base number conversion
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char	*
**         d_handler(t_format format, t_data arg);
**
**    PARAMETERS
**
**         t_format format     Structure containing information about how
**                             the argument must be formatted in the string.
**
**         t_data arg          Argument pulled off of the 'va_list'.
**
**    DESCRIPTION
**         Handles the '%d' specifier like the libc 'printf()' function.
**
**         Note: the flags and fields that apply to this specifier are
**         the following:
**
**             Flags: '-', '+', ' ', '0'
**             Width: defined or '*'
**             Precision: defined or '*'
**             Length: 'hh', 'h', 'l', 'll', 'j', 'z', 't'
**
**    RETURN VALUES
**         If successful, returns a formatted string that follows the
**         specified format; otherwise NULL.
*/

#include "../ft_printf.h"

char	*d_handler(t_format format, t_data arg)
{
	return (i_handler(format, arg));
}
