/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:34:08 by hchereau          #+#    #+#             */
/*   Updated: 2022/12/11 17:59:26 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	const size_t	size = ft_strlen(s) + 1;
	char			*strdup;

	strdup = (char *)malloc(size);
	if (strdup != NULL)
		ft_strlcpy(strdup, s, size);
	return (strdup);
}
