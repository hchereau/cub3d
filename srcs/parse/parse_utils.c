/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:53 by linux             #+#    #+#             */
/*   Updated: 2025/09/30 15:51:08 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	if (line && line[i])
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	has_cub_extension(const char *path)
{
	size_t	len;
	size_t	ext_len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	ext_len = ft_strlen(CUB_EXTENSION);
	if (len < ext_len)
		return (0);
	if (!ft_strncmp(path + len - ext_len, CUB_EXTENSION, ext_len))
		return (1);
	return (0);
}
