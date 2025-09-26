/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:51:52 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:52:01 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"


/* destroy_graphics defined in cleanup.c */

int	close_game(t_game *g)
{
	destroy_graphics(g);
	free_config(&g->cfg);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_game(g);
	if (key == KEY_W)
		g->keys.w = 1;
	if (key == KEY_S)
		g->keys.s = 1;
	if (key == KEY_A)
		g->keys.a = 1;
	if (key == KEY_D)
		g->keys.d = 1;
	if (key == KEY_LEFT)
		g->keys.left = 1;
	if (key == KEY_RIGHT)
		g->keys.right = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == KEY_W)
		g->keys.w = 0;
	if (key == KEY_S)
		g->keys.s = 0;
	if (key == KEY_A)
		g->keys.a = 0;
	if (key == KEY_D)
		g->keys.d = 0;
	if (key == KEY_LEFT)
		g->keys.left = 0;
	if (key == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}
