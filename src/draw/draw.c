/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:13:06 by lprates           #+#    #+#             */
/*   Updated: 2022/11/07 17:39:24 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_mlx *mlx, int x)
{
	size_t	j;
	t_map	*map;

	map = get_map_singleton();
	j = -1;
	while (++j < SCREEN_HEIGHT)
	{
		if (!my_get_image_pixel(&mlx->screen, x, j))
		{
			if (j < SCREEN_HEIGHT / 2)
				pixel_mlx_image_put(&mlx->screen, x, j, map->colours.celling);
			if (j > SCREEN_HEIGHT / 2)
				pixel_mlx_image_put(&mlx->screen, x, j, map->colours.floor);
		}
	}
}

void	draw_walls(t_mlx *mlx, int x, t_draw *draw)
{
	int	color;
	int	y;

	draw->step = 1.0 * TEXHEIGHT / draw->line_height;
	draw->tex_pos = draw->step * \
		(draw->draw_start - SCREEN_HEIGHT / 2 + draw->line_height / 2);
	y = draw->draw_start - 1;
	while (++y < draw->draw_end)
	{
		draw->tex_idx.y = (int)draw->tex_pos & (TEXHEIGHT - 1);
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
