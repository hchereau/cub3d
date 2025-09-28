/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:27 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 13:06:24 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	check_texture_file(char *path, t_parse_ctx *ctx)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len < 4)
		parse_error("Invalid file", ctx);
	if (ft_strncmp(path + len - 4, ".xpm", 4))
		parse_error("Invalid file", ctx);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error("Invalid file", ctx);
	if (close(fd) < 0)
		parse_error("Invalid file", ctx);
}

t_state_parsing	parse_texture(char *line, char **store, t_parse_ctx *ctx)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (*store)
		return (PARSING_FAILURE);
	if (*line == '\0')
		parse_error("Invalid file", ctx);
	check_texture_file(line, ctx);
	*store = ft_strdup(line);
	if (!*store)
		parse_error("Memory error", ctx);
	return (PARSING_SUCCESS);
}
