/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:54:15 by hchereau          #+#    #+#             */
/*   Updated: 2024/03/23 12:06:22 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (*(const unsigned char *)(s + i) == c)
			return ((void *)(s + i));
		++i;
	}
	return (NULL);
}
