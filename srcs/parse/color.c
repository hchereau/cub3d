/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:20:29 by linux             #+#    #+#             */
/*   Updated: 2025/07/21 10:30:58 by linux            ###   ########.fr       */
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

int	parse_color(char *line, t_config *cfg, int is_floor)
{
	int	color;

	while (*line == ' ')
		line++;
	if (extract_rgb(line, &color) < 0)
		return (-1);
	if (is_floor)
		cfg->floor_color = color;
	else
		cfg->ceiling_color = color;
	return (0);
}
