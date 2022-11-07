/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:52:30 by lprates           #+#    #+#             */
/*   Updated: 2022/10/08 04:22:01 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colours.h"

int	new_trgb(int const t, int const r, int const g, int const b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int const trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int const trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int const trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int const trgb)
{
	return (trgb & 0xFF);
}
