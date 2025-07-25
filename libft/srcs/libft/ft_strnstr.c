/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2022/12/11 23:26:59 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] != '\0'
			&& little[j] == big[i + j] && i + j < len)
			++j;
		if (little[j] == '\0')
			return ((char *)(big + i));
		++i;
	}
	return (NULL);
}
