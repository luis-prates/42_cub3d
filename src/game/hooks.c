/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:11:34 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/02 23:39:20 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_close(void *p)
{
	p = (void *)p;
	free_singletons();
	exit(EXIT_SUCCESS);
	return (TRUE);
}

static int	on_focus(void *p)
{
	p = (void *)p;
	//draw_map();
	return (TRUE);
}

static int	on_key_release(int keycode, void *p)
{
	t_bool		ret;
	t_player	*player;

	p = (void *)p;
	ret = FALSE;
	if (is_movement(keycode))
	{
		player = get_player_singleton();
		player->movement = NONE;
		ret = TRUE;
	}
	return (ret);
}

static int	on_key_press(int keycode, void *p)
{
	t_bool	ret;

	p = (void *)p;
	ret = TRUE;
	/*if (keycode == ESC)
		ret = on_close(NULL);
	else */if (is_movement(keycode))
		save_movement(keycode);
	else
		ret = FALSE;
	return (ret);
}

void create_hooks(void)
{
	t_mlx	*mlx;

	mlx = get_mlx_singleton();
	mlx_hook(mlx->window, KEY_PRESS, KEY_PRESS_MASK, on_key_press, NULL);
	mlx_hook(mlx->window, KEY_RELEASE, KEY_RELEASE_MASK, on_key_release, NULL);
	mlx_hook(mlx->window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, on_close, NULL);
	mlx_hook(mlx->window, VISIBILITY_NOTIFY, VISIBILITY_CHANGE_MASK, on_focus, NULL);
}
