/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:17:51 by hchereau          #+#    #+#             */
/*   Updated: 2022/12/11 16:33:26 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occu;

	c = (unsigned char)c;
	last_occu = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			last_occu = (char *)s;
		++s;
	}
	if (c == '\0')
		last_occu = (char *)s;
	return (last_occu);
}
