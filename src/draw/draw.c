/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:13:06 by lprates           #+#    #+#             */
/*   Updated: 2022/11/09 23:41:55 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_mlx *mlx, int x)
{
	size_t	j;
	t_map	*map;
	t_player	*player;

	map = get_map_singleton();
	player = get_player_singleton();
	j = -1;
	while (++j < SCREEN_HEIGHT)
	{
		if (!my_get_image_pixel(&mlx->screen, x, j))
		{
			if (j < SCREEN_HEIGHT / 2 + player->up_down * UP_DOWN_SPEED)
				pixel_mlx_image_put(&mlx->screen, x, j, map->colours.celling);
			else if (j > SCREEN_HEIGHT / 2 + player->up_down * UP_DOWN_SPEED)
				pixel_mlx_image_put(&mlx->screen, x, j, map->colours.floor);
		}
	}
}

void	draw_walls(t_mlx *mlx, int x, t_draw *draw)
{
	int	color;
	int	y;
	t_player	*player;

	player = get_player_singleton();
	y = draw->draw_start - 1;
	while (++y < draw->draw_end)
	{
		draw->tex_idx.y = (int)draw->tex_pos & (draw->wall_texture.height - 1);
		draw->tex_pos += draw->step;
		color = my_get_image_pixel(
				&draw->wall_texture,
				draw->tex_idx.x,
				draw->tex_idx.y
				);
		if (draw->side == 1)
			color = add_shade(0.6, color);
		pixel_mlx_image_put(&mlx->screen, x, y, color);
	}
}
