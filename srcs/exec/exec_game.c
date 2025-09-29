/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:49 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 16:36:54 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"

static int	loop_game(t_game *g)
{
	update_player(g);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
	return (0);
}

static int	init_game(t_game *g, t_config cfg)
{
	ft_memset(g, 0, sizeof(*g));
	g->cfg = cfg;
	g->mlx = mlx_init();
	if (!g->mlx)
		return (EXIT_FAILURE);
	g->win = mlx_new_window(g->mlx, SCREEN_W, SCREEN_H, WINDOW_TITLE);
	if (!g->win)
	{
		destroy_graphics(g);
		return (EXIT_FAILURE);
	}
	if (init_image(g) || load_textures(g))
	{
		destroy_graphics(g);
		return (EXIT_FAILURE);
	}
	init_gameplay(g);
	return (0);
}

int	exec_game(t_config cfg)
{
	t_game	g;

	if (init_game(&g, cfg))
	{
		perror("init");
		return (EXIT_FAILURE);
	}
	mlx_hook(g.win, EVENT_KEY_PRESS, MASK_KEY_PRESS, key_press, &g);
	mlx_hook(g.win, EVENT_KEY_RELEASE, MASK_KEY_RELEASE, key_release, &g);
	mlx_hook(g.win, EVENT_DESTROY, 0, close_game, &g);
	mlx_loop_hook(g.mlx, loop_game, &g);
	mlx_loop(g.mlx);
	return (0);
}
