/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:36:35 by linux             #+#    #+#             */
/*   Updated: 2025/07/25 10:34:00 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>

typedef struct s_ray
{
    double  camera;
    double  dirx;
    double  diry;
    int             mapx;
    int             mapy;
    double  distx;
    double  disty;
    double  deltax;
    double  deltay;
    int             stepx;
    int             stepy;
    int             side;
    double  perp;
}       t_ray;

static void init_dir(t_game *g)
{
    if (g->cfg.player.dir == 'N')
    {
        g->dirx = 0;
        g->diry = -1;
        g->planex = 0.66;
        g->planey = 0;
    }
    else if (g->cfg.player.dir == 'S')
    {
        g->dirx = 0;
        g->diry = 1;
        g->planex = -0.66;
        g->planey = 0;
    }
    else if (g->cfg.player.dir == 'E')
    {
        g->dirx = 1;
        g->diry = 0;
        g->planex = 0;
        g->planey = 0.66;
    }
    else if (g->cfg.player.dir == 'W')
    {
        g->dirx = -1;
        g->diry = 0;
        g->planex = 0;
        g->planey = -0.66;
    }
}

static void load_tex(t_game *g, t_img *img, char *path)
{
    img->ptr = mlx_xpm_file_to_image(g->mlx, path, &img->w, &img->h);
    if (!img->ptr)
        parse_error("Texture load error");
    img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line, &img->endian);
}

static void init_game(t_game *g, t_config cfg)
{
    ft_memset(g, 0, sizeof(*g));
    g->cfg = cfg;
    g->mlx = mlx_init();
    if (!g->mlx)
        parse_error("MLX init failed");
    g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
    g->frame.ptr = mlx_new_image(g->mlx, WIDTH, HEIGHT);
    g->frame.addr = mlx_get_data_addr(g->frame.ptr, &g->frame.bpp,
            &g->frame.line, &g->frame.endian);
    init_dir(g);
    g->px = cfg.player.pos.x + 0.5;
    g->py = cfg.player.pos.y + 0.5;
    load_tex(g, &g->tex[0], cfg.textures.north);
    load_tex(g, &g->tex[1], cfg.textures.south);
    load_tex(g, &g->tex[2], cfg.textures.west);
    load_tex(g, &g->tex[3], cfg.textures.east);
}

static int close_game(t_game *g)
{
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
    return (0);
}

static int key_press(int key, t_game *g)
{
    if (key == XK_Escape)
        close_game(g);
    if (key < 512)
        g->keys[key] = 1;
    return (0);
}

static int key_release(int key, t_game *g)
{
    if (key < 512)
        g->keys[key] = 0;
    return (0);
}

static void move_forward(t_game *g, double sp)
{
    if (g->cfg.map.grid[(int)g->py][(int)(g->px + g->dirx * sp)] != '1')
        g->px += g->dirx * sp;
    if (g->cfg.map.grid[(int)(g->py + g->diry * sp)][(int)g->px] != '1')
        g->py += g->diry * sp;
}

static void move_back(t_game *g, double sp)
{
    if (g->cfg.map.grid[(int)g->py][(int)(g->px - g->dirx * sp)] != '1')
        g->px -= g->dirx * sp;
    if (g->cfg.map.grid[(int)(g->py - g->diry * sp)][(int)g->px] != '1')
        g->py -= g->diry * sp;
}

static void move_side(t_game *g, double sp, int dir)
{
    if (g->cfg.map.grid[(int)g->py][(int)(g->px + g->planex * sp * dir)] != '1')
        g->px += g->planex * sp * dir;
    if (g->cfg.map.grid[(int)(g->py + g->planey * sp * dir)][(int)g->px] != '1')
        g->py += g->planey * sp * dir;
}

static void rotate_view(t_game *g, double ang)
{
    double  old;

    old = g->dirx;
    g->dirx = g->dirx * cos(ang) - g->diry * sin(ang);
    g->diry = old * sin(ang) + g->diry * cos(ang);
    old = g->planex;
    g->planex = g->planex * cos(ang) - g->planey * sin(ang);
    g->planey = old * sin(ang) + g->planey * cos(ang);
}

static void update_player(t_game *g)
{
    if (g->keys[XK_w])
        move_forward(g, MOVE_SPEED);
    if (g->keys[XK_s])
        move_back(g, MOVE_SPEED);
    if (g->keys[XK_a])
        move_side(g, MOVE_SPEED, -1);
    if (g->keys[XK_d])
        move_side(g, MOVE_SPEED, 1);
    if (g->keys[XK_Left])
        rotate_view(g, -ROT_SPEED);
    if (g->keys[XK_Right])
        rotate_view(g, ROT_SPEED);
}

static void setup_ray(t_game *g, t_ray *r, int x)
{
    r->camera = 2.0 * x / (double)WIDTH - 1.0;
    r->dirx = g->dirx + g->planex * r->camera;
    r->diry = g->diry + g->planey * r->camera;
    r->mapx = (int)g->px;
    r->mapy = (int)g->py;
    r->deltax = fabs(1 / r->dirx);
    r->deltay = fabs(1 / r->diry);
    if (r->dirx < 0)
    {
        r->stepx = -1;
        r->distx = (g->px - r->mapx) * r->deltax;
    }
    else
    {
        r->stepx = 1;
        r->distx = (r->mapx + 1.0 - g->px) * r->deltax;
    }
    if (r->diry < 0)
    {
        r->stepy = -1;
        r->disty = (g->py - r->mapy) * r->deltay;
    }
    else
    {
        r->stepy = 1;
        r->disty = (r->mapy + 1.0 - g->py) * r->deltay;
    }
}

static void run_dda(t_game *g, t_ray *r)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->distx < r->disty)
        {
            r->distx += r->deltax;
            r->mapx += r->stepx;
            r->side = 0;
        }
        else
        {
            r->disty += r->deltay;
            r->mapy += r->stepy;
            r->side = 1;
        }
        if (g->cfg.map.grid[r->mapy][r->mapx] == '1')
            hit = 1;
    }
    if (r->side == 0)
        r->perp = r->distx - r->deltax;
    else
        r->perp = r->disty - r->deltay;
}

static int choose_tex(t_ray *r)
{
    if (r->side == 0 && r->dirx > 0)
        return (2);
    if (r->side == 0 && r->dirx < 0)
        return (3);
    if (r->side == 1 && r->diry > 0)
        return (0);
    return (1);
}

static void draw_column(t_game *g, t_ray *r, int x)
{
    int     lineh;
    int     start;
    int     end;
    int     tex;
    int     texx;
    double  step;
    double  pos;
    int     y;
    int     texy;
    int     color;
    double  wallx;

    lineh = HEIGHT / r->perp;
    start = -lineh / 2 + HEIGHT / 2;
    if (start < 0)
        start = 0;
    end = lineh / 2 + HEIGHT / 2;
    if (end >= HEIGHT)
        end = HEIGHT - 1;
    if (r->side == 0)
        wallx = g->py + r->perp * r->diry;
    else
        wallx = g->px + r->perp * r->dirx;
    wallx -= floor(wallx);
    tex = choose_tex(r);
    texx = wallx * g->tex[tex].w;
    if ((r->side == 0 && r->dirx > 0) || (r->side == 1 && r->diry < 0))
        texx = g->tex[tex].w - texx - 1;
    step = 1.0 * g->tex[tex].h / lineh;
    pos = (start - HEIGHT / 2 + lineh / 2) * step;
    y = start;
    while (y < end)
    {
        texy = (int)pos & (g->tex[tex].h - 1);
        pos += step;
        color = *(int *)(g->tex[tex].addr + texy * g->tex[tex].line
                + texx * (g->tex[tex].bpp / 8));
        if (r->side == 1)
            color = (color >> 1) & 0x7F7F7F;
        *(int *)(g->frame.addr + y * g->frame.line
                + x * (g->frame.bpp / 8)) = color;
        y++;
    }
}

static void render(t_game *g)
{
    int     x;
    t_ray   r;

    x = 0;
    while (x < WIDTH)
    {
        setup_ray(g, &r, x);
        run_dda(g, &r);
        draw_column(g, &r, x);
        x++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
}

static int loop_hook(t_game *g)
{
    update_player(g);
    render(g);
    return (0);
}

void    exec_game(t_config cfg)
{
    t_game  g;

    init_game(&g, cfg);
    mlx_hook(g.win, KeyPress, KeyPressMask, key_press, &g);
    mlx_hook(g.win, KeyRelease, KeyReleaseMask, key_release, &g);
    mlx_hook(g.win, 17, 0, close_game, &g);
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);
}

