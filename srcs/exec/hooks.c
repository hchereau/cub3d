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

static int	*key_flag(t_keys *keys, int key)
{
	if (key == KEY_W)
		return (&keys->w);
	if (key == KEY_S)
		return (&keys->s);
	if (key == KEY_A)
		return (&keys->a);
	if (key == KEY_D)
		return (&keys->d);
	if (key == KEY_LEFT)
		return (&keys->left);
	if (key == KEY_RIGHT)
		return (&keys->right);
	return (NULL);
}

int	close_game(t_game *g)
{
	destroy_graphics(g);
	free_config(&g->cfg);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_press(int key, t_game *g)
{
	int	*flag;

	if (key == KEY_ESC)
		close_game(g);
	flag = key_flag(&g->keys, key);
	if (flag)
		*flag = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	int	*flag;

	flag = key_flag(&g->keys, key);
	if (flag)
		*flag = 0;
	return (0);
}
