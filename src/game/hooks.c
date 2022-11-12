/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:11:34 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 20:04:39 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_next_frame(void *p)
{
	t_mlx	*mlx;
	int		x;

	(void)p;
	mlx = get_mlx_singleton();
	mlx->screen = new_mlx_image(SCREEN_WIDTH, SCREEN_HEIGHT);
	x = -1;
	while (++x < SCREEN_WIDTH)
		draw_textures(x);
	mlx_put_image_to_window(
		mlx->connection,
		mlx->window,
		mlx->screen.img,
		0,
		0);
	free_mlximage(&mlx->screen);
	handle_player_movement();
	return (TRUE);
}

static int	on_focus(void *p)
{
	(void)p;
	on_next_frame(NULL);
	return (TRUE);
}

static int	on_key_press(int keycode, void *p)
{
	t_bool	ret;
	t_mlx	*mlx;

	(void)p;
	ret = TRUE;
	mlx = get_mlx_singleton();
	if (keycode == ESC)
		ret = on_close(NULL);
	else if (is_movement(keycode))
		save_movement(keycode);
	else if (keycode == TOGGLE_MOUSE)
	{
		if (mlx->toggle_mouse == TRUE)
			mlx->toggle_mouse = FALSE;
		else if (mlx->toggle_mouse == FALSE)
			mlx->toggle_mouse = TRUE;
	}
	else
		ret = FALSE;
	return (ret);
}

static int	on_key_release(int keycode, void *p)
{
	t_bool		ret;
	t_player	*player;

	(void)p;
	ret = FALSE;
	if (is_movement(keycode))
	{
		player = get_player_singleton();
		player->movement = NONE;
		ret = TRUE;
	}
	return (ret);
}

void	create_hooks(void)
{
	t_mlx	*mlx;

	mlx = get_mlx_singleton();
	//mlx_mouse_hide(mlx->connection, mlx->window);
	mlx_hook(mlx->window, KeyPress, KeyPressMask, on_key_press, NULL);
	mlx_hook(mlx->window, KeyRelease, KeyReleaseMask, on_key_release, NULL);
	mlx_hook(mlx->window, MotionNotify, PointerMotionMask, on_mouse_move, NULL);
	mlx_hook(mlx->window, DestroyNotify, StructureNotifyMask, on_close, NULL);
	mlx_hook(mlx->window, VisibilityNotify,
		VisibilityChangeMask, on_focus, NULL);
	mlx_loop_hook(mlx->connection, on_next_frame, NULL);
}
