/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:31:49 by lprates           #+#    #+#             */
/*   Updated: 2022/10/08 04:25:38 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "colours.h"
# include "constants.h"
# include "data.h"

# include <stdio.h>
# include <fcntl.h>
# include <math.h>

/* ERRORS */
void			ft_strerror(int index, char const *message);

/* SINGLETONS */
t_mlx			*get_mlx_singleton(void);
t_map			*get_map_singleton(void);
t_player		*get_player_singleton(void);
void			init_singletons(void);
void			free_singletons(void);

/* MINILIBX UTILS */
void			*new_mlx_connection(void);
void			free_mlx_connection(void **mlx_connection);
void			*new_mlx_window(int size_x, int size_y, char *title);
void			free_mlx_window(void **mlx_window);

t_mlximage		xpm_to_mlx_image(char const *file);
t_mlximage		new_mlx_image(int const width, int const height);
void			free_mlximage(t_mlximage *image);
t_mlximage		free_and_xpm_to_mlx_image(t_mlximage *image, char const *file);
void			pixel_mlx_image_put(t_mlximage *image,
					int const x, int const y, int const color);

/* PARSER */
t_bool			is_valid_cub_extention(char const *filename);
t_bool			is_texture_identifier(t_identifier const identifier_type);
t_bool			is_colour_identifier(t_identifier const identifier_type);
t_bool			is_map_character(char const c);
t_bool			are_textures_n_colours_parsed(void);

void			skip_spaces(char const **str);
t_identifier	get_identifier_type(char const *identifier);
char const		*get_identifier_description(char const *line);

t_bool			convert_texture(t_identifier const type, char const *line);
t_bool			convert_colour(t_identifier const type, char const *line);
t_bool			convert_map(int fd, char const *const line);

t_bool			parse_map(char const *filename);

#endif
