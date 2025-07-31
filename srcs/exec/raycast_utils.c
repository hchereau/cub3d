/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:33:50 by linux             #+#    #+#             */
/*   Updated: 2025/07/31 10:08:19 by linux            ###   ########.fr       */
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

void	ray_wall(t_game *g, t_ray *r)
{
	t_img	*tex;

	r->line_h = (int)(SCREEN_H / r->dist);
	r->start = -r->line_h / 2 + SCREEN_H / 2;
	if (r->start < 0)
		r->start = 0;
	r->end = r->line_h / 2 + SCREEN_H / 2;
	if (r->end >= SCREEN_H)
		r->end = SCREEN_H - 1;
	if (r->side == 0 && r->dir_x > 0)
		r->tex = 2;
	else if (r->side == 0)
		r->tex = 3;
	else if (r->side == 1 && r->dir_y > 0)
		r->tex = 0;
	else
		r->tex = 1;
	tex = &g->tex[r->tex];
	if (r->side == 0)
		r->wall_x = g->posy + r->dist * r->dir_y;
	else
		r->wall_x = g->posx + r->dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * tex->width);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		r->tex_x = tex->width - r->tex_x - 1;
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
