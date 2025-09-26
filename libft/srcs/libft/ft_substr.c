/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:54:19 by hchereau          #+#    #+#             */
/*   Updated: 2024/05/20 14:08:02 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_min(const size_t nb1, const size_t nb2)
{
	if (nb1 > nb2)
		return (nb2);
	return (nb1);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	new_len;
	size_t	slen;
	char	*substr;

	if (s != NULL)
	{
		slen = ft_strlen(s);
		new_len = 0;
		if (start <= slen)
			new_len = get_min(slen - start, len);
		else
			start = slen;
		substr = (char *)malloc((new_len + 1) * sizeof(char));
		if (substr != NULL)
			ft_strlcpy(substr, s + start, len + 1);
	}
	else
		substr = NULL;
	return (substr);
}
