/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:29:26 by idsy              #+#    #+#             */
/*   Updated: 2020/01/21 12:21:26 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         c_handler -- formatted character conversion
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char	*
**         c_handler(t_format format, t_data arg);
**
**    PARAMETERS
**
**         t_format format     Structure containing information about how
**                             the argument must be formatted in the string.
**
**         t_data arg          Argument pulled off of the 'va_list'.
**
**    DESCRIPTION
**         Handles the '%c' specifier like the libc 'printf()' function.
**
**    RETURN VALUES
**         If successful, returns a formatted string that follows the
**         specified format; otherwise NULL.
*/

#include "../ft_printf.h"

#define CHARACTER 1
#define BACKSLASH_ZERO 1

char			*c_handler(t_format format, t_data arg)
{
	char		*charstr;
	size_t		len;

	if (format.width)
		format.width -= CHARACTER;
	len = CHARACTER + format.width;
	charstr = malloc(len + BACKSLASH_ZERO);
	if (!charstr)
		exit(-1);
	if (!format.width || (format.width && format.flags & MINUS))
		charstr[0] = arg.char_;
	else
		charstr[format.width] = arg.char_;
	charstr[len] = '\0';
	if (format.width)
		ft_memset(charstr, format.pad, format.width);
	return (charstr);
}
