/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:37 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:49:45 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_graphics(t_game *g)
{
	int	i;

	if (!g)
		return ;
	if (g->screen.img)
		mlx_destroy_image(g->mlx, g->screen.img);
	i = 0;
	while (i < 4)
	{
		if (g->tex[i].img)
			mlx_destroy_image(g->mlx, g->tex[i].img);
		i++;
	}
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
}

