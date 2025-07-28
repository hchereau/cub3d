#include "game.h"

void img_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + y * img->line_len + x * (img->bpp / 8);
    *(int *)dst = color;
}

int init_image(t_game *g)
{
    g->screen.img = mlx_new_image(g->mlx, SCREEN_W, SCREEN_H);
    if (!g->screen.img)
        return (1);
    g->screen.addr = mlx_get_data_addr(g->screen.img, &g->screen.bpp,
            &g->screen.line_len, &g->screen.endian);
    g->screen.width = SCREEN_W;
    g->screen.height = SCREEN_H;
    return (0);
}

int load_texture(t_game *g, char *path, t_img *tex)
{
    tex->img = mlx_xpm_file_to_image(g->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
        return (1);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
            &tex->line_len, &tex->endian);
    return (0);
}

int load_textures(t_game *g)
{
    if (load_texture(g, g->cfg.textures.north, &g->tex[0]))
        return (1);
    if (load_texture(g, g->cfg.textures.south, &g->tex[1]))
        return (1);
    if (load_texture(g, g->cfg.textures.west, &g->tex[2]))
        return (1);
    if (load_texture(g, g->cfg.textures.east, &g->tex[3]))
        return (1);
    return (0);
}
