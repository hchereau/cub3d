/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:35:13 by linux             #+#    #+#             */
/*   Updated: 2025/07/21 10:36:15 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_texture(char *line, char **store)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (*store)
		return (-1);
	*store = ft_strdup(line);
	if (!*store)
		return (-1);
	return (0);
}
