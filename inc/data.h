/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:53 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 04:44:09 by tosilva          ###   ########.fr       */
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

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

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
}				t_mlx;

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
	int			**map;
	size_t		width;
	size_t		height;
	t_textures	textures;
	t_colours	colours;
}				t_map;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	plane;
}				t_player;

#endif
