/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:49 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:49:52 by linux            ###   ########.fr       */
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
		return (1);
	g->win = mlx_new_window(g->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!g->win)
	{
		destroy_graphics(g);
		return (1);
	}
	if (init_image(g) || load_textures(g))
	{
		destroy_graphics(g);
		return (1);
	}
	init_gameplay(g);
	return (0);
}

int	exec_game(t_config cfg)
{
	t_game	g;

	if (init_game(&g, cfg))
		return (perror("init"), 1);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 17, 0, close_game, &g);
	mlx_loop_hook(g.mlx, loop_game, &g);
	mlx_loop(g.mlx);
	return (0);
}

