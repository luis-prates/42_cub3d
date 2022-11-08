/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:46:40 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/08 00:47:44 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_bool	start_game(void)
{
	t_mlx	*mlx;

	mlx = get_mlx_singleton();
	mlx->window = new_mlx_window(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
	create_hooks();
	mlx_loop(mlx->connection);
	return (TRUE);
}
