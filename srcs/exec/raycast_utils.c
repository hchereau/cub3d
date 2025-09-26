/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:10 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:53:12 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ray_dda(t_game *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->cfg.map.grid[r->map_y][r->map_x] != '0')
			hit = 1;
	}
	if (r->side == 0)
		r->dist = (r->map_x - g->posx + (1 - r->step_x) / 2) / r->dir_x;
	else
		r->dist = (r->map_y - g->posy + (1 - r->step_y) / 2) / r->dir_y;
}

static void	draw_wall(t_game *g, t_ray *r, int x)
{
	t_img	*tex;
	int		y;
	int		ty;
	int		color;

	tex = &g->tex[r->tex];
	r->step = 1.0 * tex->height / r->line_h;
	r->tex_pos = (r->start - SCREEN_H / 2 + r->line_h / 2) * r->step;
	y = r->start;
	while (y < r->end)
	{
		ty = (int)r->tex_pos & (tex->height - 1);
		r->tex_pos += r->step;
		color = *(int *)(tex->addr + ty * tex->line_len
				+ r->tex_x * (tex->bpp / 8));
		img_pixel_put(&g->screen, x, y, color);
		++y;
	}
}

void	draw_column(t_game *g, t_ray *r, int x)
{
	int	y;

	y = 0;
	while (y < r->start)
		img_pixel_put(&g->screen, x, y++, g->cfg.ceiling_color);
	draw_wall(g, r, x);
	y = r->end;
	while (y < SCREEN_H)
		img_pixel_put(&g->screen, x, y++, g->cfg.floor_color);
}
