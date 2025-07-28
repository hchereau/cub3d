/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:36:35 by linux             #+#    #+#             */
/*   Updated: 2025/07/25 10:25:00 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"
#include <stdlib.h>

typedef struct s_ray
{
    double  dirx;
    double  diry;
    double  sdx;
    double  sdy;
    double  ddx;
    double  ddy;
    double  pwd;
    int     mx;
    int     my;
    int     sx;
    int     sy;
    int     side;
    int     tex_x;
}   t_ray;

typedef struct s_wall
{
    int     line_h;
    int     start;
    int     end;
    double  step;
    double  texpos;
}   t_wall;

static void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= img->w || y >= img->h)
        return ;
    dst = img->addr + y * img->line + x * (img->bpp / 8);
    *(int *)dst = color;
}

static int is_wall(t_game *g, int x, int y)
{
    if (x < 0 || y < 0 || x >= g->cfg.map.width || y >= g->cfg.map.height)
        return (1);
    return (g->cfg.map.grid[y][x] != '0');
}

static void load_tex(t_game *g, char *path, t_img *img)
{
    img->ptr = mlx_xpm_file_to_image(g->mlx, path, &img->w, &img->h);
    img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line, &img->endian);
}

static void fill_top(t_game *g, int x, int *y, int end)
{
    while (*y < end)
        put_pixel(&g->frame, x, (*y)++, g->cfg.ceiling_color);
}

static void fill_bottom(t_game *g, int x, int y)
{
    while (y < WIN_H)
        put_pixel(&g->frame, x, y++, g->cfg.floor_color);
}

static void init_player(t_game *g, t_config *cfg)
{
    g->posx = cfg->player.pos.x + 0.5;
    g->posy = cfg->player.pos.y + 0.5;
    if (cfg->player.dir == 'N')
    {
        g->dirx = 0;
        g->diry = -1;
    }
    else if (cfg->player.dir == 'S')
    {
        g->dirx = 0;
        g->diry = 1;
    }
    else if (cfg->player.dir == 'E')
    {
        g->dirx = 1;
        g->diry = 0;
    }
    else if (cfg->player.dir == 'W')
    {
        g->dirx = -1;
        g->diry = 0;
    }
    g->planex = -g->diry * 0.66;
    g->planey = g->dirx * 0.66;
}

static void init_frame(t_game *g)
{
    g->frame.ptr = mlx_new_image(g->mlx, WIN_W, WIN_H);
    g->frame.addr = mlx_get_data_addr(g->frame.ptr, &g->frame.bpp,
            &g->frame.line, &g->frame.endian);
    g->frame.w = WIN_W;
    g->frame.h = WIN_H;
}

static void init_textures(t_game *g, t_config *cfg)
{
    load_tex(g, cfg->textures.north, &g->tex[0]);
    load_tex(g, cfg->textures.south, &g->tex[1]);
    load_tex(g, cfg->textures.west, &g->tex[2]);
    load_tex(g, cfg->textures.east, &g->tex[3]);
}

static void init_ray(t_game *g, t_ray *r, double camx)
{
    r->dirx = g->dirx + g->planex * camx;
    r->diry = g->diry + g->planey * camx;
    r->mx = (int)g->posx;
    r->my = (int)g->posy;
    r->ddx = fabs(1.0 / r->dirx);
    r->ddy = fabs(1.0 / r->diry);
}

static void init_steps(t_game *g, t_ray *r)
{
    if (r->dirx < 0)
    {
        r->sx = -1;
        r->sdx = (g->posx - r->mx) * r->ddx;
    }
    else
    {
        r->sx = 1;
        r->sdx = (r->mx + 1.0 - g->posx) * r->ddx;
    }
    if (r->diry < 0)
    {
        r->sy = -1;
        r->sdy = (g->posy - r->my) * r->ddy;
    }
    else
    {
        r->sy = 1;
        r->sdy = (r->my + 1.0 - g->posy) * r->ddy;
    }
}

static void run_dda(t_game *g, t_ray *r)
{
    while (!is_wall(g, r->mx, r->my))
    {
        if (r->sdx < r->sdy)
        {
            r->sdx += r->ddx;
            r->mx += r->sx;
            r->side = 0;
        }
        else
        {
            r->sdy += r->ddy;
            r->my += r->sy;
            r->side = 1;
        }
    }
    if (r->side == 0)
        r->pwd = r->sdx - r->ddx;
    else
        r->pwd = r->sdy - r->ddy;
}

static t_img *choose_tex(t_game *g, t_ray *r)
{
    double  wallx;

    if (r->side == 0)
        wallx = g->posy + r->pwd * r->diry;
    else
        wallx = g->posx + r->pwd * r->dirx;
    wallx -= floor(wallx);
    r->tex_x = (int)(wallx * g->tex[0].w);
    if ((r->side == 0 && r->dirx > 0) || (r->side == 1 && r->diry < 0))
        r->tex_x = g->tex[0].w - r->tex_x - 1;
    if (r->side == 0 && r->dirx > 0)
        return (&g->tex[3]);
    if (r->side == 0)
        return (&g->tex[2]);
    if (r->diry > 0)
        return (&g->tex[1]);
    return (&g->tex[0]);
}

static void draw_column(t_game *g, int x, t_img *tex, t_ray r)
{
    t_wall  w;
    int     y;
    int     ty;

    w.line_h = (int)(WIN_H / r.pwd);
    w.start = -w.line_h / 2 + WIN_H / 2;
    if (w.start < 0)
        w.start = 0;
    w.end = w.line_h / 2 + WIN_H / 2;
    if (w.end >= WIN_H)
        w.end = WIN_H - 1;
    w.step = (double)tex->h / w.line_h;
    w.texpos = (w.start - WIN_H / 2 + w.line_h / 2) * w.step;
    y = 0;
    fill_top(g, x, &y, w.start);
    while (y <= w.end)
    {
        ty = (int)w.texpos & (tex->h - 1);
        put_pixel(&g->frame, x, y,
            *(int *)(tex->addr + ty * tex->line + r.tex_x * (tex->bpp / 8)));
        w.texpos += w.step;
        y++;
    }
    fill_bottom(g, x, y);
}

static void cast_ray(t_game *g, int x)
{
    t_ray   r;
    t_img   *tex;
    double  camx;

    camx = 2.0 * x / (double)WIN_W - 1.0;
    init_ray(g, &r, camx);
    init_steps(g, &r);
    run_dda(g, &r);
    tex = choose_tex(g, &r);
    draw_column(g, x, tex, r);
}

static void rotate_player(t_game *g, double rs)
{
    double  old;

    old = g->dirx;
    g->dirx = g->dirx * cos(rs) - g->diry * sin(rs);
    g->diry = old * sin(rs) + g->diry * cos(rs);
    old = g->planex;
    g->planex = g->planex * cos(rs) - g->planey * sin(rs);
    g->planey = old * sin(rs) + g->planey * cos(rs);
}

static void move_player(t_game *g)
{
    double  ms;
    double  rs;
    double  nx;
    double  ny;

    ms = 0.05;
    rs = 0.04;
    if (g->key[KEY_LEFT])
        rotate_player(g, -rs);
    if (g->key[KEY_RIGHT])
        rotate_player(g, rs);
    nx = g->posx + g->dirx * ms * g->key[KEY_W];
    ny = g->posy + g->diry * ms * g->key[KEY_W];
    if (!is_wall(g, (int)nx, (int)g->posy))
        g->posx = nx;
    if (!is_wall(g, (int)g->posx, (int)ny))
        g->posy = ny;
    nx = g->posx - g->dirx * ms * g->key[KEY_S];
    ny = g->posy - g->diry * ms * g->key[KEY_S];
    if (!is_wall(g, (int)nx, (int)g->posy))
        g->posx = nx;
    if (!is_wall(g, (int)g->posx, (int)ny))
        g->posy = ny;
    nx = g->posx + g->planex * ms * g->key[KEY_D];
    ny = g->posy + g->planey * ms * g->key[KEY_D];
    if (!is_wall(g, (int)nx, (int)g->posy))
        g->posx = nx;
    if (!is_wall(g, (int)g->posx, (int)ny))
        g->posy = ny;
    nx = g->posx - g->planex * ms * g->key[KEY_A];
    ny = g->posy - g->planey * ms * g->key[KEY_A];
    if (!is_wall(g, (int)nx, (int)g->posy))
        g->posx = nx;
    if (!is_wall(g, (int)g->posx, (int)ny))
        g->posy = ny;
}

static int loop_game(t_game *g)
{
    int x;

    move_player(g);
    x = 0;
    while (x < WIN_W)
    {
        cast_ray(g, x);
        x++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
    return (0);
}

static int key_press(int key, t_game *g)
{
    if (key == KEY_ESC)
        exit(0);
    if (key < 256)
        g->key[key] = 1;
    return (0);
}

static int key_release(int key, t_game *g)
{
    if (key < 256)
        g->key[key] = 0;
    return (0);
}

static int close_win(t_game *g)
{
    (void)g;
    exit(0);
    return (0);
}

int exec_game(t_config cfg)
{
    t_game  g;

    ft_bzero(&g, sizeof(g));
    g.cfg = cfg;
    g.mlx = mlx_init();
    g.win = mlx_new_window(g.mlx, WIN_W, WIN_H, "cub3d");
    init_frame(&g);
    init_textures(&g, &cfg);
    init_player(&g, &cfg);
    mlx_hook(g.win, 2, 1L << 0, key_press, &g);
    mlx_hook(g.win, 3, 1L << 1, key_release, &g);
    mlx_hook(g.win, 17, 0, close_win, &g);
    mlx_loop_hook(g.mlx, loop_game, &g);
    mlx_loop(g.mlx);
    return (0);
}

