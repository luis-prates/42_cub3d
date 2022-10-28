/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_singletons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:00:24 by lprates           #+#    #+#             */
/*   Updated: 2022/10/11 18:00:25 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*player_singleton(t_player *set_player)
{
	static t_player	*player;

	if (set_player != NULL)
	{
		player = set_player;
		set_player = 0;
	}
	return (player);
}

t_mlx	*mlx_singleton(t_mlx *set_mlx)
{
	static t_mlx	*mlx;

	if (set_mlx != NULL)
	{
		mlx = set_mlx;
		set_mlx = 0;
	}
	return (mlx);
}

t_map	*map_singleton(t_map *set_map)
{
	static t_map	*map;

	if (set_map != NULL)
	{
		map = set_map;
		set_map = 0;
	}
	return (map);
}
