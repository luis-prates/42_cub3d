/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 21:42:35 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_major_colour(int colour)
{
	return (colour >= 0 && colour <= 255);
}

static t_bool	are_valid_integers(char const **colours)
{
	t_bool	ret;
	short	idx_colour;
	size_t	str_len;
	size_t	colour_len;

	ret = TRUE;
	if (!colours[0] || !colours[1] || !colours[2])
	{
		ret = FALSE;
	}
	idx_colour = 0;
	while (idx_colour < 3 && ret == TRUE)
	{
		str_len = ft_strlen(colours[idx_colour]);
		colour_len = 0;
		while (ft_isdigit(colours[idx_colour][colour_len]))
			colour_len++;
		ret = (colour_len == str_len);
		idx_colour++;
	}
	return (ret);
}

static t_bool	split_string_to_major_colours(char const *str,
	int *const r, int *const g, int *const b)
{
	t_bool	ret;
	char	**colours;

	ret = FALSE;
	colours = ft_split(str, ',');
	if (are_valid_integers((char const **)colours))
	{
		*r = ft_atoi(colours[0]);
		*g = ft_atoi(colours[1]);
		*b = ft_atoi(colours[2]);
		ret = is_major_colour(*r);
		ret &= is_major_colour(*g);
		ret &= is_major_colour(*b);
	}
	ft_freemtx((void ***)&colours);
	return (ret);
}

static int	get_colour(char const *line)
{
	int			trgb;
	char const	*colours;
	int			r;
	int			g;
	int			b;

	trgb = -1;
	colours = NULL;
	colours = get_identifier_description(line);
	if (colours)
	{
		if (split_string_to_major_colours(colours, &r, &g, &b))
			trgb = new_trgb(0, r, g, b);
		else
			ft_strerror(INVALID_ARGUMENT, INVALID_COLOUR_DESCRIPTION);
		ft_free((void **)&colours);
	}
	else
	{
		ft_strerror(INVALID_ARGUMENT, INVALID_COLOUR_DESCRIPTION);
	}
	return (trgb);
}

t_bool	convert_colour(t_identifier const type, char const *line)
{
	t_bool	ret;
	t_map	*map;
	int		colour;

	map = get_map_singleton();
	ret = check_duplicate_keys(type);
	if (ret)
		colour = get_colour(line);
	else
		ft_strerror(BAD_INPUT, DUPLICATE_KEYS);
	if (ret && colour != -1)
		assign_colours(type, colour);
	else
		ret = FALSE;
	return (ret);
}
