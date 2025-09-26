/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:46 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 16:07:49 by linux            ###   ########.fr       */
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

t_state_parsing	parse_map(char **lines, int start, t_config *cfg)
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
		return (PARSING_FAILURE);
	cfg->map.grid = ft_calloc(cfg->map.height, sizeof(char *));
	if (!cfg->map.grid)
		return (PARSING_FAILURE);
	fill_map_grid(cfg, lines, start);
	return (PARSING_SUCCESS);
}
