/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:53:46 by lprates           #+#    #+#             */
/*   Updated: 2022/11/07 12:59:35 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colours.h"

int	add_shade(double const distance, int const colour)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(colour);
	r = get_r(colour);
	g = get_g(colour);
	b = get_b(colour);
	r -= ((int)((r >> 16) * distance) << 16);
	g -= ((int)((g >> 8) * distance) << 8);
	b -= (b * distance);
	return (t | r | g | b);
}

int	get_opposite(int const colour)
{
	int	opposite_colour;

	opposite_colour = 0xFFFFFF - colour; // ?? No transparent on "0xFFFFFF" ??
	return (opposite_colour);
}
