/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:33 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 13:07:07 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	get_cell(t_config *cfg, int x, int y)
{
	if (x < 0 || y < 0)
		return (' ');
	if (x >= cfg->map.width || y >= cfg->map.height)
		return (' ');
	return (cfg->map.grid[y][x]);
}

static int	is_border(t_config *cfg, int x, int y)
{
	if (x == 0 || y == 0)
		return (1);
	if (x >= cfg->map.width - 1)
		return (1);
	if (y >= cfg->map.height - 1)
		return (1);
	return (0);
}

static void	check_cell(t_config *cfg, int x, int y, t_parse_ctx *ctx)
{
	if (cfg->map.grid[y][x] != '0')
		return ;
	if (is_border(cfg, x, y))
		parse_error("Map not closed", ctx);
	if (get_cell(cfg, x - 1, y) == ' ' || get_cell(cfg, x + 1, y) == ' ')
		parse_error("Map not closed", ctx);
	if (get_cell(cfg, x, y - 1) == ' ' || get_cell(cfg, x, y + 1) == ' ')
		parse_error("Map not closed", ctx);
}

void	validate_map(t_config *cfg, t_parse_ctx *ctx)
{
	int	x;
	int	y;

	if (!cfg->player.dir)
		parse_error("Player missing", ctx);
	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			check_cell(cfg, x, y, ctx);
			x++;
		}
		y++;
	}
}
