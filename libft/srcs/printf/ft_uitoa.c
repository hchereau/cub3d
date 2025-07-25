/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <hchereau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:28:34 by hchereau          #+#    #+#             */
/*   Updated: 2023/02/27 15:37:02 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size_nb(size_t nb)
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

static unsigned long	get_abs(size_t n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	cp_nb(char *dest, size_t n, size_t size_nb)
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

char	*ft_uitoa(unsigned int n)
{
	const size_t	size_nb = get_size_nb(n);
	char			*str_nb;

	str_nb = (char *)malloc((size_nb + 1) * sizeof(char));
	if (str_nb != NULL)
		cp_nb(str_nb, n, size_nb);
	return (str_nb);
}
