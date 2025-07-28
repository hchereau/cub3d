/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:25:00 by linux             #+#    #+#             */
/*   Updated: 2025/07/21 10:29:55 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	set_player(t_config *cfg, int x, int y, char c)
{
	if (cfg->player.dir)
		parse_error("Multiple player");
	cfg->player.pos.x = x;
	cfg->player.pos.y = y;
	cfg->player.dir = c;
}

static int	line_len(char *line)
{
	return ((int)ft_strlen(line));
}

static void	fill_map_grid(t_config *cfg, char **lines, int start)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	while (y < cfg->map.height)
	{
		cfg->map.grid[y] = ft_calloc(cfg->map.width + 1, 1);
		ft_memset(cfg->map.grid[y], ' ', cfg->map.width);
		len = line_len(lines[start + y]);
		ft_memcpy(cfg->map.grid[y], lines[start + y], len);
		x = 0;
		while (x < len)
		{
			if (ft_strchr("NSEW", cfg->map.grid[y][x]))
			{
				set_player(cfg, x, y, cfg->map.grid[y][x]);
				cfg->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

 int	parse_map(char **lines, int start, t_config *cfg)
{
	int	i;

	cfg->map.height = 0;
	cfg->map.width = 0;
	i = start;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			if (line_len(lines[i]) > cfg->map.width)
				cfg->map.width = line_len(lines[i]);
			cfg->map.height++;
		}
		i++;
	}
	if (cfg->map.height == 0)
		return (-1);
	cfg->map.grid = ft_calloc(cfg->map.height, sizeof(char *));
	if (!cfg->map.grid)
		return (-1);
	fill_map_grid(cfg, lines, start);
	return (0);
}
