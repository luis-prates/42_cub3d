/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:46:40 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/07 17:58:01 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_bool	start_game()
{
	t_mlx	*mlx;

	mlx = get_mlx_singleton();
	create_hooks();

	// TODO DELETE
	t_map *map = get_map_singleton();
	if (map->map)
	{
		for (size_t y = 0; y < map->height; y++)
		{
			for (size_t x = 0; x < map->width; x++)
				printf("%i", map->map[y][x]);
			printf("\n");
		}
	}

	mlx_loop(mlx->connection);
	return (TRUE);
}
