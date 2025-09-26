/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:52:22 by hucherea          #+#    #+#             */
/*   Updated: 2024/09/06 13:57:08 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_tab(bool *ascii_verif)
{
	size_t	i;

	i = 0;
	while (i < 256)
	{
		if (i == '+' || i == '-' || (i < 32 || i > 126))
			ascii_verif[i] = true;
		else
			ascii_verif[i] = false;
		++i;
	}
}

static int	get_len_base(char *base)
{
	bool	ascii_verif[256];
	int		i;
	int		c;

	i = 0;
	fill_tab(ascii_verif);
	while (base[i] != '\0')
	{
		c = base[i];
		if (ascii_verif[c] == false)
			ascii_verif[c] = true;
		else
			return (0);
		++i;
	}
	return (i);
}

static int	get_number(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

long	convert_base_atoi(char *str, char *base, int len_base, int i)
{
	long	value;

	value = 0;
	while (str[i] != '\0' && get_number(str[i], base) != -1)
	{
		value = value * len_base + get_number(str[i], base);
		++i;
	}
	return (value);
}

int	ft_atoi_base(char *str, char *base)
{
	int		sign;
	int		i;
	int		len_base;
	long	atoi;

	atoi = 0;
	len_base = get_len_base(base);
	sign = 1;
	if (len_base > 1)
	{
		i = 0;
		while (str[i] == SPACE || (FIRST_WHITESPACE <= str[i]
				&& str[i] <= LAST_WHITESPACE))
			++i;
		while (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign *= -1;
			++i;
		}
		atoi = convert_base_atoi(str, base, len_base, i);
	}
	return (atoi * sign);
}
