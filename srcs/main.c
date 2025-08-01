/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:38:50 by linux             #+#    #+#             */
/*   Updated: 2025/07/25 09:36:13 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse.h"
#include "game.h"

int	main(int argc, char **argv)
{
	t_config	cfg;

	(void)argc;
	ft_memset(&cfg, 0, sizeof(cfg));
	if (!argv[1])
		return (printf("Error\nNo file\n"), 1);
	parse_file(argv[1], &cfg);
	printf("Loaded map %dx%d\n", cfg.map.width, cfg.map.height);
	exec_game(cfg);
	return (EXIT_SUCCESS);
}
