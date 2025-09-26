/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:27 by linux             #+#    #+#             */
/*   Updated: 2025/09/26 20:16:28 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_state_parsing	parse_texture(char *line, char **store)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (*store)
		return (PARSING_FAILURE);
	*store = ft_strdup(line);
	if (!*store)
		return (PARSING_FAILURE);
	return (PARSING_SUCCESS);
}
