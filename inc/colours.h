/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:31:05 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 04:21:39 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

int	new_trgb(int const t, int const r, int const g, int const b);

int	get_t(int const trgb);
int	get_r(int const trgb);
int	get_g(int const trgb);
int	get_b(int const trgb);

int	add_shade(double const distance, int const colour);
int	get_opposite(int const colour);

#endif
