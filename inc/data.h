/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:53 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/08 00:17:18 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <string.h>

typedef enum e_identifier
{
	INVALID,
	SPACE,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	CEILING,
	FLOOR,
	MAP
}			t_identifier;

typedef enum e_movement {
	NONE,
	FORWARD,
	BACKWARDS,
	STRAFE_L,
	STRAFE_R,
	ROTATE_L,
	ROTATE_R
}			t_movement;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_fpoint
{
	double	x;
	double	y;
}				t_fpoint;

typedef struct s_mlximage
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_mlximage;

typedef struct s_mlx
{
	void		*connection;
	void		*window;
	t_mlximage	screen;
	size_t		width;
	size_t		height;
}				t_mlx;

typedef struct s_draw
{
	int			draw_start;
	int			draw_end;
	t_fpoint	ray_dir;
	t_fpoint	side_dist;
	t_fpoint	delta_dist;
	double		perp_wall_dist;
	double		camera_x;
	t_point		map_idx;
	double		step;
	t_point		step_idx;
	double		tex_pos;
	t_point		tex_idx;
	int			side;
	double		wall_x;
	int			line_height;
	t_mlximage	wall_texture;
	int			hit;
}		t_draw;

typedef struct s_textures
{
	t_mlximage	north;
	t_mlximage	south;
	t_mlximage	west;
	t_mlximage	east;
}				t_textures;

typedef struct s_colours
{
	int	celling;
	int	floor;
}				t_colours;

typedef struct s_map
{
	char const	*filename;
	int			**map;
	size_t		width;
	size_t		height;
	t_textures	textures;
	t_colours	colours;
}				t_map;

typedef struct s_player
{
	t_fpoint	pos;
	t_fpoint	dir;
	t_fpoint	plane;
	t_movement	movement;
	t_bool		exists;
}				t_player;

#endif
