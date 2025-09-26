/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:52:55 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:52:57 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	compute_camera_and_direction(t_game *g, t_ray *r, int x)
{
	r->cam_x = 2.0 * x / SCREEN_W - 1.0;
	r->dir_x = g->dirx + g->plane_x * r->cam_x;
	r->dir_y = g->diry + g->plane_y * r->cam_x;
}

static void	init_map_position(t_game *g, t_ray *r)
{
	r->map_x = (int)g->posx;
	r->map_y = (int)g->posy;
}

static void	compute_delta(t_ray *r)
{
	if (r->dir_x != 0.0)
		r->delta_x = fabs(1.0 / r->dir_x);
	else
		r->delta_x = 1e30;
	if (r->dir_y != 0.0)
		r->delta_y = fabs(1.0 / r->dir_y);
	else
		r->delta_y = 1e30;
}

static void	compute_steps_and_sides(t_game *g, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->posx - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->posx) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->posy - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->posy) * r->delta_y;
	}
}

void	ray_init(t_game *g, t_ray *r, int x)
{
	compute_camera_and_direction(g, r, x);
	init_map_position(g, r);
	compute_delta(r);
	compute_steps_and_sides(g, r);
}
