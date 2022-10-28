/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:03:25 by lprates           #+#    #+#             */
/*   Updated: 2022/10/11 18:03:47 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_close(t_mlx *all, int code)
{
	if (all->mlx)
		mlx_destroy_window(all->mlx, all->win);
	//if (all->element)
	//	free_elements(all);
	//if (all->map)
	//	free(all->map);
	free(all);
	exit(code);
}
