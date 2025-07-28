/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:27:34 by linux             #+#    #+#             */
/*   Updated: 2025/07/25 10:20:00 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx.h"
# include "cub3d.h"
# include <math.h>

# define WIN_W 640
# define WIN_H 480

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
    void    *ptr;
    char    *addr;
    int             bpp;
    int             line;
    int             endian;
    int             w;
    int             h;
}   t_img;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_img   frame;
    t_img   tex[4];
    t_config        cfg;
    double  posx;
    double  posy;
    double  dirx;
    double  diry;
    double  planex;
    double  planey;
    int             key[256];
}   t_game;

int     exec_game(t_config cfg);

#endif
