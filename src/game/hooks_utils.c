/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:11:34 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/09 23:41:14 by lprates          ###   ########.fr       */
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
		|| keycode == LOOK_RIGHT
		|| keycode == LOOK_UP
		|| keycode == LOOK_DOWN)
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
	else if (keycode == LOOK_UP)
		player->up_down++;
	else if (keycode == LOOK_DOWN)
		player->up_down--;
}
