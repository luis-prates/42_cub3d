/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 05:51:52 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_valid_cub_extention(char const *filename)
{
	t_bool	ret;
	ssize_t	idx_extention;

	ret = TRUE;
	idx_extention = ft_strlen(filename) - 4;
	if (idx_extention < 1
		|| ft_strncmp(&filename[idx_extention], ".cub", 5) != 0)
	{
		ft_strerror(INVALID_ARGUMENT, BAD_FILE_EXTENTION);
		ret = FALSE;
	}
	return (ret);
}

t_bool	is_texture_identifier(t_identifier const identifier_type)
{
	return (identifier_type == NORTH
		|| identifier_type == SOUTH
		|| identifier_type == WEST
		|| identifier_type == EAST);
}

t_bool	is_colour_identifier(t_identifier const identifier_type)
{
	return (identifier_type == CEILING
		|| identifier_type == FLOOR);
}

t_bool	is_map_character(char const c)
{
	return (c == MAP_FLOOR
		|| c == MAP_WALL
		|| c == MAP_NORTH
		|| c == MAP_SOUTH
		|| c == MAP_WEST
		|| c == MAP_EAST);
}

t_bool	are_textures_n_colours_parsed(void)
{
	t_map	*map;

	map = get_map_singleton();
	return (map->textures.north.img
		&& map->textures.south.img
		&& map->textures.west.img
		&& map->textures.east.img
		&& map->colours.celling != -1
		&& map->colours.floor != -1);
}
