/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:31:49 by lprates           #+#    #+#             */
/*   Updated: 2022/11/03 23:39:27 by lprates          ###   ########.fr       */
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
t_bool			is_player_character(char const c);
t_bool			is_map_character(char const c);
t_bool			are_textures_n_colours_parsed(void);
t_bool			is_map_parsed(void);

char const		*skip_spaces(char const *str);
t_identifier	get_identifier_type(char const *identifier);
char const		*get_identifier_description(char const *line);

t_bool			is_line_valid(char const *line_before, char **line);
t_bool			skip_identifiers(int const fd, char const *first_line);
t_bool			alloc_n_convert_map(int const fd, char const *first_line);

t_bool			convert_texture(t_identifier const type, char const *line);
t_bool			convert_colour(t_identifier const type, char const *line);
t_bool			convert_map(int const fd, char const *line);

t_bool			parse_map(char const *filename);

/* GAME */
t_bool			start_game();

void 			create_hooks(void);
t_bool			is_movement(int keycode);
void			save_movement(int keycode);

/* DRAW (lprates) */
void			setup_rays(t_draw *draw, t_player *player);
void			setup_walls(t_draw *draw, t_player *player);
void			do_dda(t_draw *draw, t_map *map);
int				my_get_image_pixel(t_mlximage *data, int x, int y);
void			draw_walls(t_mlx *mlx, int x, t_draw *draw);
void			draw_background(t_mlx *mlx, int x);
void			player_movement(t_player *player);

#endif
