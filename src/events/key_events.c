/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:03:28 by lprates           #+#    #+#             */
/*   Updated: 2022/10/30 22:18:21 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook_press(int keycode, t_mlx *all)
{
	static int		mov = 0;
	t_player		*player;

	player = player_singleton(NULL);
	printf("keycode: %i", keycode);
	//if (keycode == 53 || keycode == 65307)
	//	window_close(all, 0);
	if (keycode == W || keycode == 119)
		player->movement = FORWARD;
	else if (keycode == S || keycode == 115)
		player->movement = BACKWARDS;
	else if (keycode == A || keycode == 97)
		player->movement = STRAFEL;
	else if (keycode == D || keycode == 100)
		player->movement = STRAFER;
	else if (keycode == RGARROW)
		player->movement = ROTR;
	else if (keycode == LFARROW)
		player->movement = ROTL;
	else
		return (0);
	return (1);
}

int	key_hook_release(int keycode, t_mlx *all)
{
	t_player		*player;

	player = player_singleton(NULL);
	player->movement = NONE;
	return (1);
}
