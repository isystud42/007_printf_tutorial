/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:06:32 by idsy              #+#    #+#             */
/*   Updated: 2020/01/07 08:32:22 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Reproduction of the libc 'vdprintf()' function.
*/

int				ft_vdprintf(int filedes, const char *format, va_list *args)
{
	int			tt_bytes;
	char		*fstr;
	size_t		len;
	int			i;

	if (!format)
		return (0);
	tt_bytes = 0;
	while (*format != '\0')
	{
		i = 0;
		while (format[i] != '\0' && format[i] != '%')
			++i;
		tt_bytes += write(filedes, format, i);
		format += i;
		if (*format == '%')
		{
			if (!(fstr = formatter(&format, args, &len)))
				return (-1);
			tt_bytes += write(filedes, fstr, len);
			free(fstr);
		}
	}
	va_end(*args);
	return (tt_bytes);
}
