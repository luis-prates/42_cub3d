/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:05:31 by lprates           #+#    #+#             */
/*   Updated: 2022/10/30 22:07:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	do_dda(t_draw *draw)
{
	while (draw->hit == 0)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			draw->side = 0;
			if (draw->step_x == -1)
				draw->orient = 3;
			else if (draw->step_x == 1)
				draw->orient = 4;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			if (draw->step_y == -1)
				draw->orient = 1;
			else if (draw->step_y == 1)
				draw->orient = 2;
			draw->side = 1;
		}
		if (worldMap[draw->map_x][draw->map_y] > 0)
			draw->hit = 1;
	}
}

void	setup_walls(t_draw *draw, t_player *player)
{
	if (draw->side == 0)
		draw->perp_wall_dist = (draw->side_dist_x - draw->delta_dist_x);
	else
		draw->perp_wall_dist = (draw->side_dist_y - draw->delta_dist_y);
	draw->line_height = (int)(SCREENHEIGHT / draw->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + SCREENHEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + SCREENHEIGHT / 2;
	if (draw->draw_end >= SCREENHEIGHT)
		draw->draw_end = SCREENHEIGHT - 1;
	if (draw->side == 0)
		draw->wall_x = player->pos_y + draw->perp_wall_dist * draw->ray_dir_y;
	else
		draw->wall_x = player->pos_x + draw->perp_wall_dist * draw->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (double)TEXWIDTH);
	if (draw->side == 0 && draw->ray_dir_x > 0)
		draw->tex_x = TEXWIDTH - draw->tex_x - 1;
	if (draw->side == 1 && draw->ray_dir_y < 0)
		draw->tex_x = TEXWIDTH - draw->tex_x - 1;
	draw->step = 1.0 * TEXHEIGHT / draw->line_height;
	draw->tex_pos = draw->step * \
		(draw->draw_start - SCREENHEIGHT / 2 + draw->line_height / 2);
}

void	setup_rays(t_draw *draw, t_player *player)
{
	draw->ray_dir_x = player->dir_x + player->plane_x * draw->camera_x;
	draw->ray_dir_y = player->dir_y + player->plane_y * draw->camera_x;
	draw->map_x = (int) player->pos_x;
	draw->map_y = (int) player->pos_y;
	if (draw->ray_dir_x == 0)
		draw->delta_dist_x = INFINITY;
	else
		draw->delta_dist_x = fabs(1 / draw->ray_dir_x);
	if (draw->ray_dir_y == 0)
		draw->delta_dist_y = INFINITY;
	else
		draw->delta_dist_y = fabs(1 / draw->ray_dir_y);
	draw->hit = 0;
	if (draw->ray_dir_x < 0)
		draw->side_dist_x = (player->pos_x - draw->map_x) * draw->delta_dist_x;
	else
		draw->side_dist_x = (draw->map_x + 1.0 - player->pos_x) \
			* draw->delta_dist_x;
	if (draw->ray_dir_y < 0)
		draw->side_dist_y = (player->pos_y - draw->map_y) * draw->delta_dist_y;
	else
		draw->side_dist_y = (draw->map_y + 1.0 - player->pos_y) \
			* draw->delta_dist_y;
	draw->step_x = 1 * round(draw->ray_dir_x / fabs(draw->ray_dir_x));
	draw->step_y = 1 * round(draw->ray_dir_y / fabs(draw->ray_dir_y));
}
