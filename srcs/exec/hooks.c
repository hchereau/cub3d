#include "game.h"
#include <stdlib.h>

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

int close_game(t_game *g)
{
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
    return (0);
}

int key_press(int key, t_game *g)
{
    if (key == KEY_ESC)
        close_game(g);
    if (key == KEY_W)
        g->keys.w = 1;
    if (key == KEY_S)
        g->keys.s = 1;
    if (key == KEY_A)
        g->keys.a = 1;
    if (key == KEY_D)
        g->keys.d = 1;
    if (key == KEY_LEFT)
        g->keys.left = 1;
    if (key == KEY_RIGHT)
        g->keys.right = 1;
    return (0);
}

int key_release(int key, t_game *g)
{
    if (key == KEY_W)
        g->keys.w = 0;
    if (key == KEY_S)
        g->keys.s = 0;
    if (key == KEY_A)
        g->keys.a = 0;
    if (key == KEY_D)
        g->keys.d = 0;
    if (key == KEY_LEFT)
        g->keys.left = 0;
    if (key == KEY_RIGHT)
        g->keys.right = 0;
    return (0);
}
