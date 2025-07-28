#include "game.h"
#include <math.h>

typedef struct s_ray
{
    double  cam_x;
    double  dir_x;
    double  dir_y;
    int             map_x;
    int             map_y;
    double  side_x;
    double  side_y;
    double  delta_x;
    double  delta_y;
    double  dist;
    int             step_x;
    int             step_y;
    int             side;
    int             line_h;
    int             start;
    int             end;
    double  wall_x;
    int             tex_x;
    int             tex;
    double  step;
    double  tex_pos;
}       t_ray;

static void set_dir_ns(t_game *g, char c)
{
    g->dirx = 0;
    g->plane_y = 0;
    if (c == 'N')
    {
        g->diry = -1;
        g->plane_x = 0.66;
    }
    else
    {
        g->diry = 1;
        g->plane_x = -0.66;
    }
}

static void set_dir_ew(t_game *g, char c)
{
    g->diry = 0;
    g->plane_x = 0;
    if (c == 'E')
    {
        g->dirx = 1;
        g->plane_y = 0.66;
    }
    else
    {
        g->dirx = -1;
        g->plane_y = -0.66;
    }
}

static void set_dir(t_game *g, char c)
{
    if (c == 'N' || c == 'S')
        set_dir_ns(g, c);
    else
        set_dir_ew(g, c);
}

static void set_player(t_game *g)
{
    g->posx = g->cfg.player.pos.x + 0.5;
    g->posy = g->cfg.player.pos.y + 0.5;
    set_dir(g, g->cfg.player.dir);
}

static void ray_init(t_game *g, t_ray *r, int x)
{
    r->cam_x = 2.0 * x / SCREEN_W - 1.0;
    r->dir_x = g->dirx + g->plane_x * r->cam_x;
    r->dir_y = g->diry + g->plane_y * r->cam_x;
    r->map_x = (int)g->posx;
    r->map_y = (int)g->posy;
    r->delta_x = fabs(1.0 / (r->dir_x == 0 ? 1e-30 : r->dir_x));
    r->delta_y = fabs(1.0 / (r->dir_y == 0 ? 1e-30 : r->dir_y));
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_x = (g->posx - r->map_x) * r->delta_x;
    }
    else
    {
        r->step_x = 1;
        r->side_x = (r->map_x + 1.0 - g->posx) * r->delta_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_y = (g->posy - r->map_y) * r->delta_y;
    }
    else
    {
        r->step_y = 1;
        r->side_y = (r->map_y + 1.0 - g->posy) * r->delta_y;
    }
}

static void ray_dda(t_game *g, t_ray *r)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_x < r->side_y)
        {
            r->side_x += r->delta_x;
            r->map_x += r->step_x;
            r->side = 0;
        }
        else
        {
            r->side_y += r->delta_y;
            r->map_y += r->step_y;
            r->side = 1;
        }
        if (g->cfg.map.grid[r->map_y][r->map_x] != '0')
            hit = 1;
    }
    if (r->side == 0)
        r->dist = (r->map_x - g->posx + (1 - r->step_x) / 2) / r->dir_x;
    else
        r->dist = (r->map_y - g->posy + (1 - r->step_y) / 2) / r->dir_y;
}

static void ray_wall(t_game *g, t_ray *r)
{
    t_img *tex;

    r->line_h = (int)(SCREEN_H / r->dist);
    r->start = -r->line_h / 2 + SCREEN_H / 2;
    if (r->start < 0)
        r->start = 0;
    r->end = r->line_h / 2 + SCREEN_H / 2;
    if (r->end >= SCREEN_H)
        r->end = SCREEN_H - 1;
    if (r->side == 0 && r->dir_x > 0)
        r->tex = 2;
    else if (r->side == 0)
        r->tex = 3;
    else if (r->side == 1 && r->dir_y > 0)
        r->tex = 0;
    else
        r->tex = 1;
    tex = &g->tex[r->tex];
    if (r->side == 0)
        r->wall_x = g->posy + r->dist * r->dir_y;
    else
        r->wall_x = g->posx + r->dist * r->dir_x;
    r->wall_x -= floor(r->wall_x);
    r->tex_x = (int)(r->wall_x * tex->width);
    if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
        r->tex_x = tex->width - r->tex_x - 1;
}

static void draw_wall(t_game *g, t_ray *r, int x)
{
    t_img *tex;
    int     y;
    int     ty;
    int     color;

    tex = &g->tex[r->tex];
    r->step = 1.0 * tex->height / r->line_h;
    r->tex_pos = (r->start - SCREEN_H / 2 + r->line_h / 2) * r->step;
    y = r->start;
    while (y < r->end)
    {
        ty = (int)r->tex_pos & (tex->height - 1);
        r->tex_pos += r->step;
        color = *(int *)(tex->addr + ty * tex->line_len
                + r->tex_x * (tex->bpp / 8));
        img_pixel_put(&g->screen, x, y, color);
        y++;
    }
}

static void draw_column(t_game *g, t_ray *r, int x)
{
    int y;

    y = 0;
    while (y < r->start)
        img_pixel_put(&g->screen, x, y++, g->cfg.ceiling_color);
    draw_wall(g, r, x);
    y = r->end;
    while (y < SCREEN_H)
        img_pixel_put(&g->screen, x, y++, g->cfg.floor_color);
}

void render_frame(t_game *g)
{
    int x;
    t_ray r;

    x = 0;
    while (x < SCREEN_W)
    {
        ray_init(g, &r, x);
        ray_dda(g, &r);
        ray_wall(g, &r);
        draw_column(g, &r, x);
        x++;
    }
}

static void rotate(t_game *g, double rs)
{
    double old;

    old = g->dirx;
    g->dirx = g->dirx * cos(rs) - g->diry * sin(rs);
    g->diry = old * sin(rs) + g->diry * cos(rs);
    old = g->plane_x;
    g->plane_x = g->plane_x * cos(rs) - g->plane_y * sin(rs);
    g->plane_y = old * sin(rs) + g->plane_y * cos(rs);
}

static void move(t_game *g, double mx, double my)
{
    if (g->cfg.map.grid[(int)(g->posy)][(int)(g->posx + mx)] == '0')
        g->posx += mx;
    if (g->cfg.map.grid[(int)(g->posy + my)][(int)(g->posx)] == '0')
        g->posy += my;
}

void update_player(t_game *g)
{
    double sp;

    sp = 0.08;
    if (g->keys.w)
        move(g, g->dirx * sp, g->diry * sp);
    if (g->keys.s)
        move(g, -g->dirx * sp, -g->diry * sp);
    if (g->keys.a)
        move(g, g->diry * sp, -g->dirx * sp);
    if (g->keys.d)
        move(g, -g->diry * sp, g->dirx * sp);
    if (g->keys.left)
        rotate(g, 0.05);
    if (g->keys.right)
        rotate(g, -0.05);
}

void init_gameplay(t_game *g)
{
    set_player(g);
}
