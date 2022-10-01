/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:53:46 by lprates           #+#    #+#             */
/*   Updated: 2022/10/01 18:51:44 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// seems to work
int	add_shade(double distance, int color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(color);
	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	r -= ((int)((r >> 16) * distance) << 16);
	g -= ((int)((g >> 8) * distance) << 8);
	b -= (b * distance);
	return (t | r | g | b);
}

// seems to work
int	get_opposite(int color)
{
	int	opposite_color;

	opposite_color = 0xFFFFFF - color;
	return (opposite_color);
}
