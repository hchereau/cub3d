/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:09:31 by hucherea          #+#    #+#             */
/*   Updated: 2024/09/21 13:24:04 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_whitespaces(const char **str)
{
	while (**str == SPACE || (**str >= FIRST_WHITESPACE
			&& **str <= LAST_WHITESPACE))
		++*str;
}

static long	pop_sign(const char **str)
{
	const char	c = **str;
	long		sign;

	sign = 1;
	if (c == '-')
		sign = -1;
	*str += (c == '+' || c == '-');
	return (sign);
}

static long	convert_str_to_long(const char *str, int sign)
{
	long	nb;
	long	prev_nb;

	nb = 0;
	while (ft_isdigit(*str))
	{
		prev_nb = nb;
		nb = nb * 10 + (*str - '0');
		if ((sign == 1 && nb < prev_nb)
			|| (sign == -1 && - nb > -prev_nb))
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		++str;
	}
	return (nb);
}

long	ft_atol(const char *str)
{
	long	sign;

	skip_whitespaces(&str);
	sign = pop_sign(&str);
	return (convert_str_to_long(str, sign) * sign);
}
