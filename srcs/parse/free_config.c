/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:36 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 16:07:41 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_map_grid(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_config(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->textures.north)
		free(cfg->textures.north);
	if (cfg->textures.south)
		free(cfg->textures.south);
	if (cfg->textures.east)
		free(cfg->textures.east);
	if (cfg->textures.west)
		free(cfg->textures.west);
	cfg->textures.north = NULL;
	cfg->textures.south = NULL;
	cfg->textures.east = NULL;
	cfg->textures.west = NULL;
	cfg->floor_set = 0;
	cfg->ceiling_set = 0;
	free_map_grid(&cfg->map);
}
