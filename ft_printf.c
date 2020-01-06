/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:49:21 by idsy              #+#    #+#             */
/*   Updated: 2020/01/06 12:49:24 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Reproduction of the libc 'printf()' function.
*/

int				ft_printf(const char *format, ...)
{
	va_list		args;

	va_start(args, format);
	return (ft_vdprintf(STDOUT, format, &args));
}
