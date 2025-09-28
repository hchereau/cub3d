/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:20 by linux             #+#    #+#             */
/*   Updated: 2025/09/26 20:16:22 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	handle_line(char *line, t_config *cfg)
{
	if (!ft_strncmp(line, "NO", 2))
		return (parse_texture(line + 2, &cfg->textures.north));
	if (!ft_strncmp(line, "SO", 2))
		return (parse_texture(line + 2, &cfg->textures.south));
	if (!ft_strncmp(line, "WE", 2))
		return (parse_texture(line + 2, &cfg->textures.west));
	if (!ft_strncmp(line, "EA", 2))
		return (parse_texture(line + 2, &cfg->textures.east));
	if (!ft_strncmp(line, "F", 1))
		return (parse_color(line + 1, cfg, 1));
	if (!ft_strncmp(line, "C", 1))
		return (parse_color(line + 1, cfg, 0));
	return (-1);
}

static int	parse_config(char **lines, t_config *cfg)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
			i++;
		else if (handle_line(lines[i], cfg) == 0)
			i++;
		else if (is_map_line(lines[i]))
			return (i);
		else
			parse_error("Invalid line");
	}
	parse_error("No map");
	return (i);
}

void	parse_file(const char *file, t_config *cfg)
{
	char	*data;
	char	**lines;
	int		map_start;

	parse_register_config(cfg);
	parse_register_lines(NULL);
	data = file_to_string(file);
	if (!data)
		parse_error("File read error");
	lines = ft_split(data, '\n');
	free(data);
	if (!lines)
		parse_error("Memory error");
	parse_register_lines(lines);
	map_start = parse_config(lines, cfg);
	if (parse_map(lines, map_start, cfg) < 0)
		parse_error("Map error");
	validate_map(cfg);
	free_split(lines);
	parse_register_lines(NULL);
	parse_register_config(NULL);
}
