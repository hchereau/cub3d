/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:27:34 by linux             #+#    #+#             */
/*   Updated: 2025/07/25 10:33:34 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx.h"
# include "cub3d.h"
# include <math.h>

# define WIDTH 640
# define HEIGHT 480
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

typedef struct s_img
{
    void    *ptr;
    char    *addr;
    int             line;
    int             bpp;
    int             endian;
    int             w;
    int             h;
}       t_img;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_img   frame;
    t_img   tex[4];
    t_config        cfg;
    double  px;
    double  py;
    double  dirx;
    double  diry;
    double  planex;
    double  planey;
    int             keys[512];
}       t_game;

void    exec_game(t_config cfg);

#endif
