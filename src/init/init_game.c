/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:57:37 by lprates           #+#    #+#             */
/*   Updated: 2022/10/11 22:59:06 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_mlx *all, t_player *player)
{
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, screenWidth,
			screenHeight, "The Guy Game!");
	write(1, "Aqui\n", 5);
	player->pos_x = 12;
	player->pos_y = 20;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	write(1, "Aqui\n", 5);
	player_singleton(player);
	mlx_singleton(all);
}

void	new_image(t_mlx	*all)
{
	all->img.img = mlx_new_image(all->mlx, screenWidth, screenHeight);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
						&all->img.endian);
}
