/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:52:50 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:52:52 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	move(t_game *g, double mx, double my)
{
	if (g->cfg.map.grid[(int)(g->posy)][(int)(g->posx + mx)] == '0')
		g->posx += mx;
	if (g->cfg.map.grid[(int)(g->posy + my)][(int)(g->posx)] == '0')
		g->posy += my;
}

static void	rotate(t_game *g, double rs)
{
	double	old;

	old = g->dirx;
	g->dirx = g->dirx * cos(rs) - g->diry * sin(rs);
	g->diry = old * sin(rs) + g->diry * cos(rs);
	old = g->plane_x;
	g->plane_x = g->plane_x * cos(rs) - g->plane_y * sin(rs);
	g->plane_y = old * sin(rs) + g->plane_y * cos(rs);
}

void	update_player(t_game *g)
{
	double	sp;

	sp = 0.08;
	if (g->keys.w)
		move(g, g->dirx * sp, g->diry * sp);
	if (g->keys.s)
		move(g, -g->dirx * sp, -g->diry * sp);
	if (g->keys.a)
		move(g, g->diry * sp, -g->dirx * sp);
	if (g->keys.d)
		move(g, -g->diry * sp, g->dirx * sp);
	if (g->keys.left)
		rotate(g, 0.05);
	if (g->keys.right)
		rotate(g, -0.05);
}
