/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:41:09 by lprates           #+#    #+#             */
/*   Updated: 2022/10/30 22:16:02 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_player *player)
{
	int		reverse;
	int		map_x;
	int		map_y;

	reverse = 1;
	map_x = (int)(player->pos_x + reverse * player->dir_x * MOVESPEED);
	map_y = (int)(player->pos_y + reverse * player->dir_y * MOVESPEED);
	if (player->movement == BACKWARDS)
		reverse = -1;
	if (worldMap[map_x][(int)player->pos_y] == 0)
		player->pos_x += reverse * player->dir_x * MOVESPEED;
	if (worldMap[(int)player->pos_x][map_y] == 0)
		player->pos_y += reverse * player->dir_y * MOVESPEED;
}

static void	strafe_player(t_player *player)
{
	int		reverse;
	int		map_x;
	int		map_y;

	reverse = 1;
	map_x = (int)(player->pos_x - reverse * player->dir_y * MOVESPEED);
	map_y = (int)(player->pos_y + reverse * player->dir_x * MOVESPEED);
	if (player->movement == STRAFER)
		reverse = -1;
	if (worldMap[map_x][(int)player->pos_y] == 0)
		player->pos_x -= reverse * player->dir_y * MOVESPEED;
	if (worldMap[(int) player->pos_x][map_y] == 0)
		player->pos_y += reverse * player->dir_x * MOVESPEED;
}

static void	rotate_player(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	int		reverse;

	reverse = 1;
	if (player->movement == ROTR)
		reverse = -1;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(reverse * ROTSPEED) \
		- player->dir_y * sin(reverse * ROTSPEED);
	player->dir_y = old_dir_x * sin(reverse * ROTSPEED) \
		+ player->dir_y * cos(reverse * ROTSPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(reverse * ROTSPEED) \
		- player->plane_y * sin(reverse * ROTSPEED);
	player->plane_y = old_plane_x * sin(reverse * ROTSPEED) \
		+ player->plane_y * cos(reverse * ROTSPEED);
}

void	player_movement(t_player *player)
{
	if (player->movement == FORWARD || player->movement == BACKWARDS)
		move_player(player);
	if (player->movement == STRAFEL || player->movement == STRAFER)
		strafe_player(player);
	if (player->movement == ROTR || player->movement == ROTL)
		rotate_player(player);
}
