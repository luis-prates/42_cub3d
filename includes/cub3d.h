/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:31:49 by lprates           #+#    #+#             */
/*   Updated: 2022/09/24 01:25:14 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <sys/time.h>
# include <mlx.h>

// defines input key codes
# define W 13
# define S 1
# define A 0
# define D 2
# define LFARROW 65361
# define RGARROW 65363
# define ESCAPE 65307

typedef enum e_movement {
	NONE,
	FORWARD,
	BACKWARDS,
	STRAFEL,
	STRAFER,
	ROTL,
	ROTR
}			t_movement;

// lodev tutorial starts
# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480
# define texWidth 64
# define texHeight 64

// lodev tutorial ends

typedef struct s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_movement	movement;
}			t_player;

typedef struct s_draw
{
	int		draw_start;
	int		draw_end;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	camera_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
}		t_draw;

typedef struct s_color
{
	int	bottom;
	int	top;
}		t_color;

/*typedef struct s_texture
{
	mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
}		t_texture;*/

typedef struct s_map
{
	char		**map;
	int			size_x;
	int			size_y;
	t_color		colors;
	//t_texture	textures;
}				t_map;

// from soLong
//! convert to s_mlx
typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_data		img;
	int			v_size;
	int			h_size;
}				t_mlx;

// struct map (char **, sizeX, sizeY, t_color, t_textures), player, s_mlx(img/mlx/win/screensize)
// singleton map, player, s_mlx

// from soLong end

int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			add_shade(double distance, int color);
int			get_oposite(int color);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			my_get_image_pixel(t_data *data, int x, int y);

// init
void		nit_game(t_mlx *all, t_player *player);
void		new_image(t_mlx	*all);

// events
int			window_close(t_mlx *all, int code);
int			key_hook_press(int keycode, t_mlx *all);
int			key_hook_release(int keycode, t_mlx *all);

// singletons
t_player	*player_singleton(t_player *set_player);
t_mlx		*mlx_singleton(t_mlx *set_mlx);
t_map		*map_singleton(t_map *set_map);

#endif
