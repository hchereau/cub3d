/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:20:29 by linux             #+#    #+#             */
/*   Updated: 2025/07/31 10:43:59 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:05:00 by toi               #+#    #+#             */
/*   Updated: 2025/07/31 11:05:00 by toi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	calculate_line_limits(t_ray *r)
{
	r->line_h = (int)(SCREEN_H / r->dist);
	r->start = -r->line_h / 2 + SCREEN_H / 2;
	if (r->start < 0)
		r->start = 0;
	r->end = r->line_h / 2 + SCREEN_H / 2;
	if (r->end >= SCREEN_H)
		r->end = SCREEN_H - 1;
}

static void	select_texture_id(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->dir_x > 0.0)
			r->tex = 2;
		else
			r->tex = 3;
	}
	else
	{
		if (r->dir_y > 0.0)
			r->tex = 0;
		else
			r->tex = 1;
	}
}

static void	calculate_wall_x(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->wall_x = g->posy + r->dist * r->dir_y;
	else
		r->wall_x = g->posx + r->dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
}

static void	calculate_tex_x(t_game *g, t_ray *r)
{
	t_img	*tex;

	tex = &g->tex[r->tex];
	r->tex_x = (int)(r->wall_x * tex->width);
	if ((r->side == 0 && r->dir_x > 0.0)
		|| (r->side == 1 && r->dir_y < 0.0))
		r->tex_x = tex->width - r->tex_x - 1;
}

void	ray_wall(t_game *g, t_ray *r)
{
	calculate_line_limits(r);
	select_texture_id(r);
	calculate_wall_x(g, r);
	calculate_tex_x(g, r);
}
