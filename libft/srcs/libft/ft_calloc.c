/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:54:12 by imback            #+#    #+#             */
/*   Updated: 2023/12/08 12:09:07 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	const size_t	size_total = nmemb * size;
	void			*ptr;

	ptr = NULL;
	if (size_total == 0 || nmemb <= SIZE_MAX / size)
		ptr = malloc(size_total);
	if (ptr != NULL)
		ft_bzero(ptr, size_total);
	return (ptr);
}
