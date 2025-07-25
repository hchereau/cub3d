/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:04:55 by hchereau          #+#    #+#             */
/*   Updated: 2024/03/25 18:53:30 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	i;
	char	*strmapi;

	if (s == NULL)
		strmapi = NULL;
	else if (f == NULL)
		strmapi = ft_strdup(s);
	else
	{
		size = ft_strlen(s);
		strmapi = (char *)malloc((size + 1) * sizeof(char));
		if (strmapi != NULL)
		{
			i = 0;
			while (i < size)
			{
				strmapi[i] = f(i, s[i]);
				++i;
			}
			strmapi[size] = '\0';
		}
	}
	return (strmapi);
}
