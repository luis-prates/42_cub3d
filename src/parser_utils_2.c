/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/16 12:59:27 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_bool	is_player_character(char const c)
{
	return (c == MAP_NORTH
		|| c == MAP_SOUTH
		|| c == MAP_WEST
		|| c == MAP_EAST);
}

t_bool	is_map_character(char const c)
{
	return (c == MAP_FLOOR
		|| c == MAP_WALL
		|| is_player_character(c));
}

t_bool	is_map_parsed(void)
{
	t_map	*map;

	map = get_map_singleton();
	return (map->map != NULL);
}
