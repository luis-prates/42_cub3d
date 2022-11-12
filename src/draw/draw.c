/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:13:06 by lprates           #+#    #+#             */
/*   Updated: 2022/11/11 20:06:13 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_mlx *mlx, int x)
{
	size_t		j;
	t_map		*map;
	t_player	*player;

	map = get_map_singleton();
	player = get_player_singleton();
	j = -1;
	while (++j < SCREEN_HEIGHT)
	{
		if (!get_image_pixel(&mlx->screen, x, j))
		{
			if (j < SCREEN_HEIGHT / 2 + player->up_down * UP_DOWN_SPEED)
				pixel_mlx_image_put(&mlx->screen, x, j, map->colours.celling);
			else if (j > SCREEN_HEIGHT / 2 + player->up_down * UP_DOWN_SPEED)
				pixel_mlx_image_put(&mlx->screen, x, j, map->colours.floor);
		}
	}
}

static void	draw_walls(t_mlx *mlx, int x, t_draw *draw)
{
	t_player	*player;
	int			color;
	int			y;

	player = get_player_singleton();
	draw->step = (double)draw->wall_texture.height / draw->line_height;
	draw->tex_pos = draw->step * (draw->draw_start - (SCREEN_HEIGHT / 2
				+ player->up_down * UP_DOWN_SPEED) + draw->line_height / 2);
	y = draw->draw_start - 1;
	while (++y < draw->draw_end)
	{
		draw->tex_idx.y = (int)draw->tex_pos & (draw->wall_texture.height - 1);
		draw->tex_pos += draw->step;
		color = get_image_pixel(
				&draw->wall_texture,
				draw->tex_idx.x,
				draw->tex_idx.y
				);
		if (draw->side == 1)
			color = add_shade(0.6, color);
		pixel_mlx_image_put(&mlx->screen, x, y, color);
	}
}

void	draw_textures(int x)
{
	t_mlx		*mlx;
	t_player	*player;
	t_map		*map;
	t_draw		draw;

	mlx = get_mlx_singleton();
	player = get_player_singleton();
	map = get_map_singleton();
	ft_bzero((void *)&draw, sizeof(t_draw));
	draw.camera_x = (2 * x / (double)SCREEN_WIDTH) - 1;
	setup_rays(&draw, player);
	do_dda(&draw, map);
	setup_walls(&draw, player);
	draw_walls(mlx, x, &draw);
	draw_background(mlx, x);
}
