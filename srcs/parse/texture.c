/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:27 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 14:10:42 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	texture_error(char *label, char *suffix, char *detail,
			t_parse_ctx *ctx)
{
	char	msg[64];

	msg[0] = '\0';
	ft_strlcpy(msg, label, sizeof(msg));
	ft_strlcat(msg, suffix, sizeof(msg));
	if (detail)
		parse_error_detail(msg, detail, ctx);
	else
		parse_error(msg, ctx);
}

static void	check_texture_file(char *path, t_parse_ctx *ctx, char *label)
{
	size_t	len;
	int		fd;
	ssize_t	read_ret;
	char	buffer;

	len = ft_strlen(path);
	if (len < 4)
		texture_error(label, " path too short", NULL, ctx);
	if (ft_strncmp(path + len - 4, ".xpm", 4))
		texture_error(label, " must use .xpm", NULL, ctx);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		texture_error(label, " file missing: ", path, ctx);
	read_ret = read(fd, &buffer, 1);
	if (read_ret <= 0)
	{
		close(fd);
		texture_error(label, " file empty: ", path, ctx);
	}
	if (close(fd) < 0)
		texture_error(label, " close failure: ", path, ctx);
}

static void	check_texture_syntax(char *line, char *label, t_parse_ctx *ctx)
{
	if (ft_strchr(line, '\t'))
		texture_error(label, " line has invalid syntax", NULL, ctx);
	if (*line != ' ')
		texture_error(label, " line has invalid syntax", NULL, ctx);
}

t_state_parsing	parse_texture(char *line, char **store, t_parse_ctx *ctx,
			char *label)
{
	check_texture_syntax(line, label, ctx);
	while (*line == ' ')
		line++;
	if (*store)
		texture_error(label, " duplicated", NULL, ctx);
	if (*line == '\0')
		texture_error(label, " path missing", NULL, ctx);
	check_texture_file(line, ctx, label);
	*store = ft_strdup(line);
	if (!*store)
		parse_error("Memory error", ctx);
	return (PARSING_SUCCESS);
}
