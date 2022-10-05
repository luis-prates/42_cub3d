/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:31:49 by lprates           #+#    #+#             */
/*   Updated: 2022/10/02 13:05:59 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "constants.h"

# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>


typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
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
	int		pos_x;
	int		pos_y;
	char	direction;
}				t_player;

// typedef struct s_mlximage
// {
// 	void	*image;
// 	void	*address;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	int		width;
// 	int		height;
// }				t_mlximage;

// // Colours
// int		new_trgb(int t, int r, int g, int b);
// int		get_t(int trgb);
// int		get_r(int trgb);
// int		get_g(int trgb);
// int		get_b(int trgb);
// int		add_shade(double distance, int color); // ?? distance
// int		get_opposite(int color);

#endif
