/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:27:34 by linux             #+#    #+#             */
/*   Updated: 2025/07/31 09:40:26 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx.h"
# include "cub3d.h"
# include <math.h>

# define SCREEN_W 1920
# define SCREEN_H 1080
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		tex[4];
	t_keys		keys;
	t_config	cfg;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		plane_x;
	double		plane_y;
}	t_game;


typedef struct s_ray
{
	double	cam_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	dist;
	int		step_x;
	int		step_y;
	int		side;
	int		line_h;
	int		start;
	int		end;
	double	wall_x;
	int		tex_x;
	int		tex;
	double	step;
	double	tex_pos;
}	t_ray;

int		exec_game(t_config cfg);
void	render_frame(t_game *g);
void	update_player(t_game *g);
int		init_image(t_game *g);
int		load_textures(t_game *g);
void	init_gameplay(t_game *g);
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
int		close_game(t_game *g);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	ray_init(t_game *g, t_ray *r, int x);
void	ray_dda(t_game *g, t_ray *r);
void	ray_wall(t_game *g, t_ray *r);
void	draw_column(t_game *g, t_ray *r, int x);

#endif
