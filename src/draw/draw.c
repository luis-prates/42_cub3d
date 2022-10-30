/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:09:19 by lprates           #+#    #+#             */
/*   Updated: 2022/10/30 22:04:43 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// send floor and ceiling colors
void	draw_background(t_mlx *all, int x)
{
	size_t	j;

	j = -1;
	while (++j < SCREENHEIGHT)
	{
		if (!my_get_image_pixel(&all->img, x, j))
		{
			if (j < SCREENHEIGHT / 2)
				my_mlx_pixel_put(&all->img, x, j, create_trgb(0, 0, 255, 0));
			if (j > SCREENHEIGHT / 2)
				my_mlx_pixel_put(&all->img, x, j, create_trgb(0, 0, 255, 255));
		}
	}
}

void	draw_walls(t_mlx *all, int x, t_draw *draw, t_data *texture_image)
{
	int		color;
	int		y;

	draw->step = 1.0 * TEXHEIGHT / draw->line_height;
	draw->tex_pos = draw->step * \
		(draw->draw_start - SCREENHEIGHT / 2 + draw->line_height / 2);
	y = draw->draw_start - 1;
	while (++y < draw->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos & (TEXHEIGHT - 1);
		draw->tex_pos += draw->step;
		color = my_get_image_pixel(
				&texture_image[draw->orient - 1],
				draw->tex_x,
				draw->tex_y
				);
		if (draw->side == 1)
			color = add_shade(0.6, color);
		my_mlx_pixel_put(&all->img, x, y, color);
	}
}

void	draw_textures(t_mlx *all, int x, t_data *texture_image)
{
	t_draw		*draw;
	t_player	*player;

	player = player_singleton(NULL);
	draw = malloc(sizeof(t_draw));
	draw->camera_x = 2 * x / (double) SCREENWIDTH - 1;
	setup_rays(draw, player);
	do_dda(draw);
	setup_walls(draw, player);
	draw_walls(all, x, draw, texture_image);
	draw_background(all, x);
}
