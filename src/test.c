/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/09/24 11:36:55 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* static double posX = 22, posY = 12;  //x and y start position
** static double dirX = -1, dirY = 0; //initial direction vector
** planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
*/
// move texttures part to init/parse
int	render_next_frame(t_mlx *all)
{
	t_player		*player;
	int				x;
	t_data			texture_image[4];
	char			*paths[4] = {"./wall_textures/colorstone.xpm", "./wall_textures/redbrick.xpm","./wall_textures/purplestone.xpm","./wall_textures/eagle.xpm"};
	unsigned long tw, th;
	int v = -1;

	while (++v < 4)
	{
		texture_image[v].img = mlx_xpm_file_to_image(all->mlx, paths[v], &tw, &th);
		texture_image[v].addr = mlx_get_data_addr(texture_image[v].img, &texture_image[v].bits_per_pixel, &texture_image[v].line_length, &texture_image[v].endian);	
	}
	player = player_singleton(NULL);
	new_image(all);
	x = -1;
	while (++x < SCREENWIDTH)
		draw_textures(all, x, texture_image);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_destroy_image(all->mlx, all->img.img);
	player_movement(player);
	return (0);
}

int	main(void)
{
	t_mlx		*all;
	t_player	*player;

	all = malloc(sizeof(t_mlx));
	player = malloc(sizeof(t_player));
	if (!all || !player)
	{
		printf("Error\nCouldn't allocate memory.");
		exit(-1);
	}
	all->mlx = 0;
	init_game(all, player);
	all = mlx_singleton(NULL);
	//mlx_key_hook(all->win, key_hook, all);
	mlx_hook(all->win, 2, (1L<<0), key_hook_press, all);
	mlx_hook(all->win, 3, (1L<<1), key_hook_release, all);
	mlx_loop_hook(all->mlx, render_next_frame, all);
	mlx_loop(all->mlx);
	return (0);
}
