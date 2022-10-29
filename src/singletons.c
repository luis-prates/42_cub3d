/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:15:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/16 13:21:59 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	*get_mlx_singleton(void)
{
	static t_mlx	mlx;

	return (&mlx);
}

t_map	*get_map_singleton(void)
{
	static t_map	map;

	return (&map);
}

t_player	*get_player_singleton(void)
{
	static t_player	player;

	return (&player);
}

void	init_singletons(void)
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;

	mlx = get_mlx_singleton();
	mlx->connection = new_mlx_connection();
	map = get_map_singleton();
	ft_bzero((void *)map, sizeof(t_map));
	map->colours.celling = -1;
	map->colours.floor = -1;
	player = get_player_singleton();
	ft_bzero((void *)player, sizeof(t_player));
}

//! Always free mlx connection after freed images/windows
//* Free in inverse
void	free_singletons(void)
{
	t_map		*map;
	t_mlx		*mlx;

	map = get_map_singleton();
	if (map->map)
	{
		for (size_t y = 0; y < map->height; y++)
		{
			for (size_t x = 0; x < map->width; x++)
				printf("%i", map->map[y][x]);
			printf("\n");
		}
	}
	free_mlximage((void *)&map->textures.west);
	free_mlximage((void *)&map->textures.east);
	free_mlximage((void *)&map->textures.south);
	free_mlximage((void *)&map->textures.north);
	ft_freemtx((void ***)&map->map);
	mlx = get_mlx_singleton();
	free_mlximage((void *)&mlx->screen);
	free_mlx_window(&mlx->window);
	free_mlx_connection(&mlx->connection);
}
