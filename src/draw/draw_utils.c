/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:05:56 by lprates           #+#    #+#             */
/*   Updated: 2022/11/10 09:39:10 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_get_image_pixel(t_mlximage *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)dst);
}

void	do_dda(t_draw *draw, t_map *map)
{
	while (draw->hit == 0)
	{
		if (draw->side_dist.x < draw->side_dist.y)
		{
			draw->side_dist.x += draw->delta_dist.x;
			draw->map_idx.x += draw->step_idx.x;
			draw->side = 0;
			if (draw->step_idx.x == -1)
				draw->wall_texture = map->textures.west;
			else if (draw->step_idx.x == 1)
				draw->wall_texture = map->textures.east;
		}
		else
		{
			draw->side_dist.y += draw->delta_dist.y;
			draw->map_idx.y += draw->step_idx.y;
			if (draw->step_idx.y == -1)
				draw->wall_texture = map->textures.north;
			else if (draw->step_idx.y == 1)
				draw->wall_texture = map->textures.south;
			draw->side = 1;
		}
		if (map->map[draw->map_idx.x][draw->map_idx.y] > 0)
			draw->hit = 1;
	}
}

void	setup_walls(t_draw *draw, t_player *player)
{
	if (draw->side == 0)
		draw->perp_wall_dist = (draw->side_dist.x - draw->delta_dist.x);
	else
		draw->perp_wall_dist = (draw->side_dist.y - draw->delta_dist.y);
	draw->line_height = (int)(SCREEN_HEIGHT / draw->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + SCREEN_HEIGHT / 2 + player->updown * UPDOWNROTSPEED;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + SCREEN_HEIGHT / 2 + player->updown * UPDOWNROTSPEED;
	if (draw->draw_end >= SCREEN_HEIGHT)
		draw->draw_end = SCREEN_HEIGHT;
	if (draw->side == 0)
		draw->wall_x = player->pos.y + draw->perp_wall_dist * draw->ray_dir.y;
	else
		draw->wall_x = player->pos.x + draw->perp_wall_dist * draw->ray_dir.x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_idx.x = (int)(draw->wall_x * (double)draw->wall_texture.width);
	if (draw->side == 0 && draw->ray_dir.x > 0)
		draw->tex_idx.x = draw->wall_texture.width - draw->tex_idx.x - 1;
	if (draw->side == 1 && draw->ray_dir.y < 0)
		draw->tex_idx.x = draw->wall_texture.width - draw->tex_idx.x - 1;
	draw->step = 1.0 * draw->wall_texture.height / draw->line_height;
	draw->tex_pos = draw->step * \
		(draw->draw_start - SCREEN_HEIGHT / 2 + draw->line_height / 2);
}

void	setup_rays(t_draw *draw, t_player *player)
{
	draw->ray_dir.x = player->dir.x + player->plane.x * draw->camera_x;
	draw->ray_dir.y = player->dir.y + player->plane.y * draw->camera_x;
	draw->map_idx.x = (int) player->pos.x;
	draw->map_idx.y = (int) player->pos.y;
	if (draw->ray_dir.x == 0)
		draw->delta_dist.x = INFINITY;
	else
		draw->delta_dist.x = fabs(1 / draw->ray_dir.x);
	if (draw->ray_dir.y == 0)
		draw->delta_dist.y = INFINITY;
	else
		draw->delta_dist.y = fabs(1 / draw->ray_dir.y);
	draw->hit = 0;
	if (draw->ray_dir.x < 0)
		draw->side_dist.x = (player->pos.x - draw->map_idx.x) * draw->delta_dist.x;
	else
		draw->side_dist.x = (draw->map_idx.x + 1.0 - player->pos.x) \
			* draw->delta_dist.x;
	if (draw->ray_dir.y < 0)
		draw->side_dist.y = (player->pos.y - draw->map_idx.y) * draw->delta_dist.y;
	else
		draw->side_dist.y = (draw->map_idx.y + 1.0 - player->pos.y) \
			* draw->delta_dist.y;
	draw->step_idx.x = 1 * round(draw->ray_dir.x / fabs(draw->ray_dir.x));
	draw->step_idx.y = 1 * round(draw->ray_dir.y / fabs(draw->ray_dir.y));
}
