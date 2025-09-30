/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:46 by linux             #+#    #+#             */
/*   Updated: 2025/09/30 15:42:27 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#define MAP_TILES " 01NSEW"
#define PLAYER_TILES "NSEW"

static void	check_map_char(char c, t_parse_ctx *ctx)
{
	if (!ft_strchr(MAP_TILES, c))
		parse_error("Invalid character in map", ctx);
}

static void	set_player(t_config *cfg, t_coord pos, char tile,
			t_parse_ctx *ctx)
{
	if (cfg->player.dir)
		parse_error("Multiple player", ctx);
	cfg->player.pos = pos;
	cfg->player.dir = tile;
}

static void	process_map_row(t_config *cfg, int y, int len, t_parse_ctx *ctx)
{
	int		x;
	t_coord	pos;

	x = 0;
	while (x < len)
	{
		check_map_char(cfg->map.grid[y][x], ctx);
		if (ft_strchr(PLAYER_TILES, cfg->map.grid[y][x]))
		{
			pos.x = x;
			pos.y = y;
			set_player(cfg, pos, cfg->map.grid[y][x], ctx);
			cfg->map.grid[y][x] = '0';
		}
		x++;
	}
}

static void	fill_map_grid(t_config *cfg, char **lines, int start,
			t_parse_ctx *ctx)
{
	int	y;
	int	len;

	y = 0;
	while (y < cfg->map.height)
	{
		cfg->map.grid[y] = ft_calloc(cfg->map.width + 1, 1);
		if (!cfg->map.grid[y])
			parse_error("Memory error", ctx);
		ft_memset(cfg->map.grid[y], ' ', cfg->map.width);
		len = (int)ft_strlen(lines[start + y]);
		ft_memcpy(cfg->map.grid[y], lines[start + y], len);
		process_map_row(cfg, y, len, ctx);
		y++;
	}
}

t_state_parsing	parse_map(char **lines, int start, t_config *cfg,
			t_parse_ctx *ctx)
{
	int	i;

	cfg->map.height = 0;
	cfg->map.width = 0;
	i = start;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			if ((int)ft_strlen(lines[i]) > cfg->map.width)
				cfg->map.width = (int)ft_strlen(lines[i]);
			cfg->map.height++;
		}
		i++;
	}
	if (cfg->map.height == 0)
		return (PARSING_FAILURE);
	cfg->map.grid = ft_calloc(cfg->map.height, sizeof(char *));
	if (!cfg->map.grid)
		return (PARSING_FAILURE);
	fill_map_grid(cfg, lines, start, ctx);
	return (PARSING_SUCCESS);
}
