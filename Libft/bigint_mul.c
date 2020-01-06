/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:50:19 by idsy              #+#    #+#             */
/*   Updated: 2020/01/06 10:50:32 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bigint	bigint_mul(t_bigint num, int multiplier, char *base)
{
	int8_t		tmp;
	int8_t		intbase;
	int32_t		carry;
	int32_t		i;

	num = ft_strdup(num);
	intbase = ft_strlen(base);
	carry = 0;
	i = ft_strlen(num) - 1;
	while (i >= 0)
	{
		if (num[i] == '.')
			--i;
		tmp = (ft_strchr(base, num[i]) - base);
		num[i--] = base[(tmp * multiplier + carry) % intbase];
		carry = ((tmp * multiplier) + carry) / intbase;
	}
	if (carry)
		num = ft_strprepend(num, ft_itoa(carry), 1, 1);
	return (num);
}

/*
**    DESCRIPTION
**         Wrapper function that allows to clean up & free certain variables
**         after function execution.
**
**    PARAMETERS
**
**         int free_num         Integer (boolean) to signal whether
**                              or not to free the variable(s).
**
**    FREE'D PARAMETERS
**
**         - t_bigint num
*/

t_bigint	bigint_mulfre(t_bigint num, int multiplier, char *base,
				int free_num)
{
	t_bigint	res;

	res = bigint_mul(num, multiplier, base);
	if (free_num && num)
		free((void *)num);
	return (res);
}
