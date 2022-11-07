/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:38:48 by lprates           #+#    #+#             */
/*   Updated: 2022/11/07 12:13:50 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_player *player)
{
	int		reverse;
	int		map_x;
	int		map_y;
	t_map	*map;

	map = get_map_singleton();
	reverse = 1;
	map_x = (int)(player->pos.x + reverse * player->dir.x * MOVESPEED);
	map_y = (int)(player->pos.y + reverse * player->dir.y * MOVESPEED);
	if (player->movement == BACKWARDS)
		reverse = -1;
	if (map->map[map_x][(int)player->pos.y] == 0)
		player->pos.x += reverse * player->dir.x * MOVESPEED;
	if (map->map[(int)player->pos.x][map_y] == 0)
		player->pos.y += reverse * player->dir.y * MOVESPEED;
}

static void	strafe_player(t_player *player)
{
	int		reverse;
	int		map_x;
	int		map_y;
	t_map	*map;

	map = get_map_singleton();
	reverse = 1;
	map_x = (int)(player->pos.x - reverse * player->dir.y * MOVESPEED);
	map_y = (int)(player->pos.y + reverse * player->dir.x * MOVESPEED);
	if (player->movement == STRAFE_R)
		reverse = -1;
	if (map->map[map_x][(int)player->pos.y] == 0)
	{
		player->pos.x -= reverse * player->dir.y * MOVESPEED;
	}
	if (map->map[(int) player->pos.x][map_y] == 0)
		player->pos.y += reverse * player->dir.x * MOVESPEED;
	printf("mapX: %i, posX: %f, mapY: %i, posY: %f\n", map_x, player->pos.x, map_y, player->pos.y);
}

static void	rotate_player(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	int		reverse;
	t_map	*map;

	map = get_map_singleton();
	reverse = 1;
	if (player->movement == ROTATE_R)
		reverse = -1;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(reverse * ROTSPEED) \
		- player->dir.y * sin(reverse * ROTSPEED);
	player->dir.y = old_dir_x * sin(reverse * ROTSPEED) \
		+ player->dir.y * cos(reverse * ROTSPEED);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(reverse * ROTSPEED) \
		- player->plane.y * sin(reverse * ROTSPEED);
	player->plane.y = old_plane_x * sin(reverse * ROTSPEED) \
		+ player->plane.y * cos(reverse * ROTSPEED);
}

void	player_movement(t_player *player)
{
	if (player->movement == FORWARD || player->movement == BACKWARDS)
		move_player(player);
	if (player->movement == STRAFE_L || player->movement == STRAFE_R)
		strafe_player(player);
	if (player->movement == ROTATE_L || player->movement == ROTATE_R)
		rotate_player(player);
}
