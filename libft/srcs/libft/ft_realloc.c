/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:25:47 by linux             #+#    #+#             */
/*   Updated: 2025/07/16 09:26:10 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t old, size_t new)
{
	void	*d;

	if (new == 0)
		return (free(p), NULL);
	if (!p)
		return (malloc(new));
	if (old >= new)
		return (p);
	d = malloc(new);
	if (!d)
		return (free(p), NULL);
	ft_memcpy(d, p, old);
	return (free(p), d);
}
