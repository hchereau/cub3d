/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:38:52 by hchereau          #+#    #+#             */
/*   Updated: 2023/12/13 19:06:23 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	start_string_trim(const char *s1, const char *set)
{
	size_t	size_start;

	size_start = 0;
	if (set != NULL)
	{
		while (s1[size_start] != '\0'
			&& (ft_strchr(set, s1[size_start]) != NULL))
			++size_start;
	}
	return (size_start);
}

size_t	len_string_trim(const char *s1, const char *set)
{
	size_t	len;

	len = ft_strlen(s1);
	if (set != NULL)
	{
		while (len > 0 && (ft_strchr(set, s1[len - 1]) != NULL))
			--len;
	}
	return (len);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trim;
	size_t	start;
	size_t	len;

	trim = NULL;
	if (s1 != NULL)
	{
		start = start_string_trim(s1, set);
		len = len_string_trim(s1 + start, set);
		trim = ft_substr(s1 + start, 0, len);
	}
	return (trim);
}

/*
	process

	parcourir la string en verifiant les si un caractere est trim
	(verifier si chaines null et si trim null)
	malloc sur taille de string - trim (protection malloc)
	parcourir la string pour copier les character sans trim

*/

/*
   process
   -> alloue malloc trim
   -> verifier si trim est pas null
   -> verifier tout les caractere au debut
   -> verifier tous les caractere a la fin
   -> reecrire s1 dans trim
   -> return trim
 */

/*
   start_string_trim
process:
->
 */
