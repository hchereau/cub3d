/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:20 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 14:10:42 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	ensure_required_config(t_config *cfg, t_parse_ctx *ctx)
{
	if (!cfg->textures.north)
		parse_error("Missing north texture", ctx);
	if (!cfg->textures.south)
		parse_error("Missing south texture", ctx);
	if (!cfg->textures.west)
		parse_error("Missing west texture", ctx);
	if (!cfg->textures.east)
		parse_error("Missing east texture", ctx);
	if (!cfg->floor_set)
		parse_error("Missing floor color", ctx);
	if (!cfg->ceiling_set)
		parse_error("Missing ceiling color", ctx);
}

static char	**load_lines(const char *file, t_parse_ctx *ctx)
{
	char	*data;
	char	**lines;

	data = file_to_string(file);
	if (!data)
		parse_error("File read error", ctx);
	lines = ft_split(data, '\n');
	free(data);
	if (!lines)
		parse_error("Memory error", ctx);
	return (lines);
}

static int	handle_line(char *line, t_config *cfg, t_parse_ctx *ctx)
{
	if (!ft_strncmp(line, "NO", 2))
		return (parse_texture(line + 2, &cfg->textures.north,
				ctx, "north texture"));
	if (!ft_strncmp(line, "SO", 2))
		return (parse_texture(line + 2, &cfg->textures.south,
				ctx, "south texture"));
	if (!ft_strncmp(line, "WE", 2))
		return (parse_texture(line + 2, &cfg->textures.west,
				ctx, "west texture"));
	if (!ft_strncmp(line, "EA", 2))
		return (parse_texture(line + 2, &cfg->textures.east,
				ctx, "east texture"));
	if (!ft_strncmp(line, "F", 1))
		return (parse_color(line + 1, cfg, 1, ctx));
	if (!ft_strncmp(line, "C", 1))
		return (parse_color(line + 1, cfg, 0, ctx));
	return (-1);
}

static int	parse_config(char **lines, t_config *cfg, t_parse_ctx *ctx)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
			i++;
		else if (handle_line(lines[i], cfg, ctx) == 0)
			i++;
		else if (is_map_line(lines[i]))
			return (i);
		else
			parse_error("Invalid line", ctx);
	}
	parse_error("No map", ctx);
	return (i);
}

void	parse_file(const char *file, t_config *cfg)
{
	t_parse_ctx	ctx;
	char		**lines;
	int			map_start;

	ctx.cfg = cfg;
	ctx.lines = NULL;
	cfg->floor_set = 0;
	cfg->ceiling_set = 0;
	if (!has_cub_extension(file))
		parse_error_detail("Invalid map extension: ", file, &ctx);
	lines = load_lines(file, &ctx);
	ctx.lines = lines;
	map_start = parse_config(lines, cfg, &ctx);
	ensure_required_config(cfg, &ctx);
	if (parse_map(lines, map_start, cfg, &ctx) < 0)
		parse_error("Map error", &ctx);
	validate_map(cfg, &ctx);
	free_split(lines);
	ctx.lines = NULL;
}
