/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:30 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:53:34 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	parse_value(char **str)
{
	int	val;

	if (!ft_isdigit(**str))
		return (-1);
	val = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	return (val);
}

static int	extract_rgb(char *line, int *color)
{
	int	r;
	int	g;
	int	b;

	r = parse_value(&line);
	if (*line != ',')
		return (-1);
	line++;
	g = parse_value(&line);
	if (*line != ',')
		return (-1);
	line++;
	b = parse_value(&line);
	while (*line == ' ')
		line++;
	if (*line != '\0')
		return (-1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

static void	color_line_error(int is_floor, const char *suffix,
			t_parse_ctx *ctx)
{
	char	msg[64];

	msg[0] = '\0';
	if (is_floor)
		ft_strlcpy(msg, "Floor color", sizeof(msg));
	else
		ft_strlcpy(msg, "Ceiling color", sizeof(msg));
	if (suffix)
		ft_strlcat(msg, suffix, sizeof(msg));
	parse_error(msg, ctx);
}

static void	store_color(t_config *cfg, int color, int is_floor)
{
	if (is_floor)
	{
		cfg->floor_color = color;
		cfg->floor_set = 1;
	}
	else
	{
		cfg->ceiling_color = color;
		cfg->ceiling_set = 1;
	}
}

int	parse_color(char *line, t_config *cfg, int is_floor, t_parse_ctx *ctx)
{
	int	color;

	if ((is_floor && cfg->floor_set) || (!is_floor && cfg->ceiling_set))
		color_line_error(is_floor, " duplicated", ctx);
	if (*line == '\0')
		color_line_error(is_floor, " missing", ctx);
	if (ft_strchr(line, '\t'))
		color_line_error(is_floor, " line has invalid syntax", ctx);
	if (*line != ' ')
		color_line_error(is_floor, " line has invalid syntax", ctx);
	while (*line == ' ')
		line++;
	if (*line == '\0')
		color_line_error(is_floor, " missing", ctx);
	if (extract_rgb(line, &color) < 0)
		color_line_error(is_floor, " invalid", ctx);
	store_color(cfg, color, is_floor);
	return (0);
}
