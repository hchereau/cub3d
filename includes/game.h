/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:27:34 by linux             #+#    #+#             */
/*   Updated: 2025/07/25 09:37:12 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx.h"
# include "cub3d.h"

# define SCREEN_W 640
# define SCREEN_H 480

typedef struct s_img
{
    void    *img;
    char    *addr;
    int             bpp;
    int             line_len;
    int             endian;
    int             width;
    int             height;
}       t_img;

typedef struct s_keys
{
    int     w;
    int     s;
    int     a;
    int     d;
    int     left;
    int     right;
}       t_keys;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_img   screen;
    t_img   tex[4];
    t_keys  keys;
    t_config        cfg;
    double  posx;
    double  posy;
    double  dirx;
    double  diry;
    double  plane_x;
    double  plane_y;
}       t_game;

int             exec_game(t_config cfg);
void    render_frame(t_game *g);
void    update_player(t_game *g);
int             init_image(t_game *g);
int             load_textures(t_game *g);
void    init_gameplay(t_game *g);
int             key_press(int key, t_game *g);
int             key_release(int key, t_game *g);
int             close_game(t_game *g);
void    img_pixel_put(t_img *img, int x, int y, int color);

#endif
