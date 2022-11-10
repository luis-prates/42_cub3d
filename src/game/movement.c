/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:38:48 by lprates           #+#    #+#             */
/*   Updated: 2022/11/10 09:21:41 by tosilva          ###   ########.fr       */
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
	if (player->movement == BACKWARDS)
		reverse = -1;
	else
		reverse = 1;
	map_x = (int)(player->pos.x + reverse * player->dir.x * MOVE_SPEED);
	map_y = (int)(player->pos.y + reverse * player->dir.y * MOVE_SPEED);
	if (map->map[map_x][(int)player->pos.y] == 0)
		player->pos.x += reverse * player->dir.x * MOVE_SPEED;
	if (map->map[(int)player->pos.x][map_y] == 0)
		player->pos.y += reverse * player->dir.y * MOVE_SPEED;
}

static void	strafe_player(t_player *player)
{
	int		reverse;
	int		map_x;
	int		map_y;
	t_map	*map;

	map = get_map_singleton();
	if (player->movement == STRAFE_R)
		reverse = -1;
	else
		reverse = 1;
	map_x = (int)(player->pos.x - reverse * player->dir.y * MOVE_SPEED);
	map_y = (int)(player->pos.y + reverse * player->dir.x * MOVE_SPEED);
	if (map->map[map_x][(int)player->pos.y] == 0)
		player->pos.x -= reverse * player->dir.y * MOVE_SPEED;
	if (map->map[(int) player->pos.x][map_y] == 0)
		player->pos.y += reverse * player->dir.x * MOVE_SPEED;
}

static void	rotate_player(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	int		reverse;

	if (player->movement == ROTATE_R)
		reverse = -1;
	else
		reverse = 1;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(reverse * ROT_SPEED) \
		- player->dir.y * sin(reverse * ROT_SPEED);
	player->dir.y = old_dir_x * sin(reverse * ROT_SPEED) \
		+ player->dir.y * cos(reverse * ROT_SPEED);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(reverse * ROT_SPEED) \
		- player->plane.y * sin(reverse * ROT_SPEED);
	player->plane.y = old_plane_x * sin(reverse * ROT_SPEED) \
		+ player->plane.y * cos(reverse * ROT_SPEED);
}

void	handle_player_movement(void)
{
	t_player	*player;

	player = get_player_singleton();
	if (player->movement == FORWARD || player->movement == BACKWARDS)
		move_player(player);
	else if (player->movement == STRAFE_L || player->movement == STRAFE_R)
		strafe_player(player);
	else if (player->movement == ROTATE_L || player->movement == ROTATE_R)
		rotate_player(player);
	if ((player->pos.x - (int)player->pos.x) < 0.000001)
		player->pos.x += 0.010000;
	else if ((player->pos.x - (int)player->pos.x) > 0.999999)
		player->pos.x -= 0.010000;
	if ((player->pos.y - (int)player->pos.y) < 0.000001)
		player->pos.y += 0.010000;
	else if ((player->pos.y - (int)player->pos.y) > 0.999999)
		player->pos.y -= 0.010000;
}
