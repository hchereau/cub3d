/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:43 by linux             #+#    #+#             */
/*   Updated: 2025/07/31 09:27:04 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	set_dir_ns(t_game *g, char c)
{
	g->dirx = 0;
	g->plane_y = 0;
	if (c == 'N')
	{
		g->diry = -1;
		g->plane_x = 0.66;
	}
	else
	{
		g->diry = 1;
		g->plane_x = -0.66;
	}
}

static void	set_dir_ew(t_game *g, char c)
{
	g->diry = 0;
	g->plane_x = 0;
	if (c == 'E')
	{
		g->dirx = 1;
		g->plane_y = 0.66;
	}
	else
	{
		g->dirx = -1;
		g->plane_y = -0.66;
	}
}

static void	set_dir(t_game *g, char c)
{
	if (c == 'N' || c == 'S')
		set_dir_ns(g, c);
	else
		set_dir_ew(g, c);
}

static void	set_player(t_game *g)
{
	g->posx = g->cfg.player.pos.x + 0.5;
	g->posy = g->cfg.player.pos.y + 0.5;
	set_dir(g, g->cfg.player.dir);
}

void	init_gameplay(t_game *g)
{
	set_player(g);
}
