/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:46:40 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/07 17:12:37 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textures(t_mlx *mlx, int x)
{
	t_draw		draw;
	t_player	*player;
	t_map		*map;

	player = get_player_singleton();
	map = get_map_singleton();
	//draw->wall_texture = malloc(sizeof(t_mlximage));
	//printf("", player->pos.x, player->pos.y, player->dir.x, player->dir.y, player->plane.x, player->plane)
	draw.camera_x = 2 * x / (double) SCREENWIDTH - 1;
	setup_rays(&draw, player);
	do_dda(&draw, map);
	setup_walls(&draw, player);
	draw_walls(mlx, x, &draw);
	draw_background(mlx, x);
}

void	new_image(t_mlx	*mlx)
{
	mlx->screen.img = mlx_new_image(mlx->connection, SCREENWIDTH, SCREENHEIGHT);
	mlx->screen.addr = mlx_get_data_addr(
			mlx->screen.img,
			&mlx->screen.bits_per_pixel,
			&mlx->screen.line_length,
			&mlx->screen.endian
			);
}

int	render_next_frame(t_mlx *mlx)
{
	t_player	*player;
	int			x;

	player = get_player_singleton();
	new_image(mlx);
	x = -1;
	while (++x < SCREENWIDTH)
		draw_textures(mlx, x);
	mlx_put_image_to_window(
		mlx->connection,
		mlx->window,
		mlx->screen.img,
		0,
		0);
	mlx_destroy_image(mlx->connection, mlx->screen.img);
	player_movement(player);
	return (0);
}

t_bool	start_game()
{
	t_mlx	*mlx;

	mlx = get_mlx_singleton();
	create_hooks();


	// TODO DELETE
	t_map *map = get_map_singleton();
	if (map->map)
	{
		for (size_t y = 0; y < map->height; y++)
		{
			for (size_t x = 0; x < map->width; x++)
				printf("%i", map->map[y][x]);
			printf("\n");
		}
	}

	mlx_loop_hook(mlx->connection, render_next_frame, mlx);
	//mlx_loop(mlx->connection);
	return (TRUE);
}
