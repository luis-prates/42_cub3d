/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colour_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:40:24 by lprates           #+#    #+#             */
/*   Updated: 2022/11/11 21:41:57 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_colours(t_identifier const type, int colour)
{
	t_map		*map;

	map = get_map_singleton();
	if (type == CEILING)
	{
		map->colours.celling = colour;
		map->ceil_assigned = TRUE;
	}
	else if (type == FLOOR)
	{
		map->colours.floor = colour;
		map->floor_assigned = TRUE;
	}
}
