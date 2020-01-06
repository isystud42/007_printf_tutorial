/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_round.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:50:06 by idsy              #+#    #+#             */
/*   Updated: 2020/01/06 10:50:34 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		norm_counter(char *b, char *decpt, int prec)
{
	if (ft_strchr(b, *(decpt + prec + 1)) - b >= (long)ft_strlen(b) / 2)
		return (1);
	return (0);
}

t_bigint		bigint_round(t_bigint num, char *base, int prec)
{
	int32_t		decimals;
	char		*decpt;
	char		*rndr;

	num = ft_strdup(num);
	prec = (prec >= 0) ? prec : 6;
	if ((decpt = ft_strchr(num, '.')))
	{
		decimals = (ft_strlen(num) - 1) - (decpt - num);
		if (decimals > prec || prec == 0)
		{
			if (norm_counter(base, decpt, prec))
			{
				rndr = ft_dtoa_base(ft_pow(10, -prec), base, 0, prec);
				num = bigint_addfre(num, rndr, base, 3);
			}
		}
		else
			num = ft_strappend(num, ft_padding(prec - decimals, '0'), 1, 1);
		num[(ft_strchr(num, '.') - num) + ((prec) ? prec + 1 : 0)] = '\0';
	}
	else if (prec)
		num = ft_strappend(ft_strappend(num, ".", 1, 0),
				ft_padding(prec, '0'), 1, 1);
	return (num);
}

t_bigint		bigint_roundfre(t_bigint num, char *base, int precision,
					int free_num)
{
	t_bigint	res;

	res = bigint_round(num, base, precision);
	if (free_num && num)
		free((void *)num);
	return (res);
}
