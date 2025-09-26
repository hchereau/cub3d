/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:43:46 by imback            #+#    #+#             */
/*   Updated: 2023/12/12 23:54:52 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	size1;
	size_t	size2;

	size1 = 0;
	size2 = 0;
	if (s1 != NULL)
		size1 = ft_strlen(s1);
	if (s2 != NULL)
		size2 = ft_strlen(s2);
	join = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (join != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(join, s1, size1 + 1);
		if (s2 != NULL)
			ft_strlcpy(join + size1, s2, size2 + 1);
	}
	return (join);
}

/*
	process
		-> malloc de la chaine avec la taille des deux string
			(protection malloc et chaines null)
		-> strlcpy de la chaine 1 (protection chaine null)
		-> strlcat seconde chaine
*/
