/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:26:04 by akharrou          #+#    #+#             */
/*   Updated: 2020/01/06 09:58:07 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BIAS          16383
#define MANT_SIZE     63
#define _15BITS       32767
#define MAX_EXPONENT  16321
#define EMPTY         9223372036854775808u

char	*ft_ldtoa_base(long double n, char *base, int width, int precision)
{
	t_long_double	num;
	t_bigint		res;

	num.ldbl_.val = n;
	num.sign = num.ldbl_.body[9] >> 7 != 0;
	num.exponent = (*(short *)&num.ldbl_.body[8] & _15BITS) - BIAS - MANT_SIZE;
	num.mantissa = *(intmax_t *)num.ldbl_.body;
	if ((num.exponent == MAX_EXPONENT && num.mantissa == EMPTY))
		return ((num.sign) ? ft_strdup("-inf") : ft_strdup("inf"));
	if (num.exponent == MAX_EXPONENT && num.mantissa != EMPTY)
		return (ft_strdup("nan"));
	res = ft_utoa_base(num.mantissa, DECIMAL_BASE, 0);
	if (num.exponent > 0)
		while (num.exponent-- > 0)
			res = bigint_mulfre(res, 2, base, 1);
	else
		while (num.exponent++ < 0)
			res = bigint_divfre(res, 2, base, 1);
	precision = (precision >= 0) ? precision : 6;
	res = bigint_roundfre(res, base, precision, 1);
	res = ft_strprepend(res, ft_padding(width - ft_strlen(res), '0'), 1, 1);
	return ((num.sign) ? ft_strprepend(res, "-", 1, 0) : res);
}
