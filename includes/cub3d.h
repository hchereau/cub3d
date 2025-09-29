/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:51:14 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 15:51:17 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef int		t_color;
typedef char	t_direction;
typedef char **	t_grid;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_map
{
	t_grid	grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_texture;

typedef struct s_player
{
	t_coord		pos;
	t_direction	dir;
}	t_player;

typedef struct s_config
{
	t_texture	textures;
	t_color		floor_color;
	t_color		ceiling_color;
	int			floor_set;
	int			ceiling_set;
	t_map		map;
	t_player	player;
}	t_config;

#endif
