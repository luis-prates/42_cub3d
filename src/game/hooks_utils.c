/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:11:34 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 20:11:04 by lprates          ###   ########.fr       */
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

int	on_mouse_move(void *p)
{
	t_mlx		*mlx;
	t_player	*player;
	int			x;
	int			y;

	(void)p;
	mlx = get_mlx_singleton();
	player = get_player_singleton();
	if (mlx->toggle_mouse)
	{
		mlx_mouse_get_pos(mlx->connection, mlx->window, &x, &y);
		if (x < SCREEN_WIDTH / 2)
			player->movement = ROTATE_L;
		else if (x > SCREEN_WIDTH / 2)
			player->movement = ROTATE_R;
		else
			player->movement = NONE;
		if (x != SCREEN_WIDTH / 2 || y != SCREEN_HEIGHT / 2)
			mlx_mouse_move(mlx->connection, mlx->window,
				SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else
		player->movement = NONE;
	return (TRUE);
}

int	on_close(void *p)
{
	(void)p;
	free_singletons();
	exit(EXIT_SUCCESS);
	return (TRUE);
}
