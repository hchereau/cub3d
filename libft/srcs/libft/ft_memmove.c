/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:07:25 by imback            #+#    #+#             */
/*   Updated: 2023/12/05 19:30:40 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*reverse_memcpy(void *dest, const void *src, size_t n)
{
	while (n > 0)
	{
		((uint8_t *) dest)[n - 1] = ((uint8_t *) src)[n - 1];
		--n;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		dest = reverse_memcpy(dest, src, n);
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}
