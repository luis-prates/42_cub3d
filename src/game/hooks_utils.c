/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:11:34 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/08 00:41:40 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_movement(int keycode)
{
	t_bool	ret;

	ret = FALSE;
	if (keycode == MOVE_UP
		|| keycode == MOVE_DOWN
		|| keycode == MOVE_LEFT
		|| keycode == MOVE_RIGHT
		|| keycode == LOOK_LEFT
		|| keycode == LOOK_RIGHT)
		ret = TRUE;
	return (ret);
}

void	save_movement(int keycode)
{
	t_player	*player;

	player = get_player_singleton();
	if (keycode == MOVE_UP)
		player->movement = FORWARD;
	else if (keycode == MOVE_DOWN)
		player->movement = BACKWARDS;
	else if (keycode == MOVE_LEFT)
		player->movement = STRAFE_L;
	else if (keycode == MOVE_RIGHT)
		player->movement = STRAFE_R;
	else if (keycode == LOOK_LEFT)
		player->movement = ROTATE_L;
	else if (keycode == LOOK_RIGHT)
		player->movement = ROTATE_R;
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
