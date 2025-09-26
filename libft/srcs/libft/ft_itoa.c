/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:13:28 by hchereau          #+#    #+#             */
/*   Updated: 2024/03/22 18:21:20 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size_nb(int nb)
{
	size_t	size;

	size = (nb == 0);
	while (nb != 0)
	{
		nb /= 10;
		++size;
	}
	return (size);
}

static unsigned long	get_abs(const int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	cp_nb(char *const dest, const int n, const size_t size_nb)
{
	size_t			i;
	unsigned int	abs_n;

	abs_n = get_abs(n);
	i = 0;
	while (i < size_nb)
	{
		dest[size_nb - i - 1] = (abs_n % 10) + '0';
		abs_n /= 10;
		++i;
	}
	dest[size_nb] = '\0';
}

char	*ft_itoa(int n)
{
	const size_t	size_nb = get_size_nb(n);
	const bool		is_neg = (n < 0);
	char			*str_nb;

	str_nb = (char *)malloc((size_nb + is_neg + 1) * sizeof(char));
	if (str_nb != NULL)
	{
		if (n < 0)
			str_nb[0] = '-';
		cp_nb(str_nb + is_neg, n, size_nb);
	}
	return (str_nb);
}
