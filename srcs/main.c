/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:16:40 by linux             #+#    #+#             */
/*   Updated: 2025/09/28 18:04:59 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse.h"
#include "game.h"

static int	print_usage(const char *prog)
{
	printf("Error\nUsage: %s <map_file.cub>\n", prog);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	ft_memset(&cfg, 0, sizeof(cfg));
	if (argc != 2)
		return (print_usage(argv[0]));
	parse_file(argv[1], &cfg);
	printf("Loaded map %dx%d\n", cfg.map.width, cfg.map.height);
	(void)exec_game(cfg);
	free_config(&cfg);
	return (EXIT_SUCCESS);
}
