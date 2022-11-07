/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:11:34 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/07 18:03:25 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	draw_textures(int x)
{
	t_mlx		*mlx;
	t_player	*player;
	t_map		*map;
	t_draw		draw;

	mlx = get_mlx_singleton();
	player = get_player_singleton();
	map = get_map_singleton();
	//draw->wall_texture = malloc(sizeof(t_mlximage));
	//printf("", player->pos.x, player->pos.y, player->dir.x, player->dir.y, player->plane.x, player->plane)
	draw.camera_x = 2 * x / (double) SCREEN_WIDTH - 1;
	setup_rays(&draw, player);
	do_dda(&draw, map);
	setup_walls(&draw, player);
	draw_walls(mlx, x, &draw);
	draw_background(mlx, x);
}

static int	on_next_frame(void *p)
{
	t_mlx		*mlx;
	t_player	*player;
	int			x;

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
	on_next_frame(NULL); // TODO Needed ?
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
	if (keycode == ESC)
		ret = on_close(NULL);
	else if (is_movement(keycode))
		save_movement(keycode);
	else
		ret = FALSE;
	return (ret);
}


void create_hooks(void)
{
	t_mlx	*mlx;

	mlx = get_mlx_singleton();
	mlx_loop_hook(mlx->connection, on_next_frame, NULL);
	mlx_hook(mlx->window, KEY_PRESS, KEY_PRESS_MASK, on_key_press, NULL);
	mlx_hook(mlx->window, KEY_RELEASE, KEY_RELEASE_MASK, on_key_release, NULL);
	mlx_hook(mlx->window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, on_close, NULL);
	mlx_hook(mlx->window, VISIBILITY_NOTIFY, VISIBILITY_CHANGE_MASK, on_focus, NULL);
}
