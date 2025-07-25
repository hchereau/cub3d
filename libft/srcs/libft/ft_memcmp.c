/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 00:15:49 by hchereau          #+#    #+#             */
/*   Updated: 2022/12/11 18:53:48 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((uint8_t *)s1)[i] != ((uint8_t *)s2)[i])
			return (((uint8_t *)s1)[i] - ((uint8_t *)s2)[i]);
		++i;
	}
	return (0);
}
