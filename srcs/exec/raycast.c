/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:13:10 by linux             #+#    #+#             */
/*   Updated: 2025/07/31 09:34:29 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	render_frame(t_game *g)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < SCREEN_W)
	{
		ray_init(g, &r, x);
		ray_dda(g, &r);
		ray_wall(g, &r);
		draw_column(g, &r, x);
		++x;
	}
}



