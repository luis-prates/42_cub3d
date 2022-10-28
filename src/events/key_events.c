/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:03:28 by lprates           #+#    #+#             */
/*   Updated: 2022/10/11 18:04:52 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook_press(int keycode, t_mlx *all)
{
	static int	mov = 0;

	//if (keycode == 53 || keycode == 65307)
	//	window_close(all, 0);
	if (keycode == W || keycode == 119)
		forward = 1;
	else if (keycode == S || keycode == 115)
		backwards = 1;
	else if (keycode == A || keycode == 97)
		left = 1;
	else if (keycode == D || keycode == 100)
		right = 1;
	else
		return (0);
	printf("Number of movements: %i\n", ++mov);
	return (1);
}

int	key_hook_release(int keycode, t_mlx *all)
{
	forward = 0;
	backwards = 0;
	left = 0;
	right = 0;
	return (1);
}
