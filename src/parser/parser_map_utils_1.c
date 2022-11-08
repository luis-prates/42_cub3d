/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:35:53 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/16 13:28:48 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	gap_found(char const c1, char const c2)
{
	t_bool	c1_as_space;
	t_bool	c2_as_space;

	c1_as_space = (c1 == ' ' && (c2 != MAP_WALL && c2 != ' '));
	c2_as_space = ((c1 != MAP_WALL && c1 != ' ') && c2 == ' ');
	return (c1_as_space || c2_as_space);
}

static t_bool
	is_map_closed(char const *line_before, char const *line, size_t idx)
{
	t_bool	ret;

	ret = TRUE;
	if (idx <= 0 || !line_before || ft_strlen(line_before) - 1 <= idx
		|| !line[idx + 1] || !line_before[idx + 1])
	{
		if (gap_found(' ', line[idx]))
			ret = FALSE;
		if (!line[idx + 1] && line_before && ft_strlen(line_before) - 1 >= idx)
		{
			while (line_before[idx] && ret != FALSE)
				if (gap_found(line_before[idx++], ' '))
					ret = FALSE;
		}
	}
	else if (gap_found(line[idx - 1], line[idx])
		|| gap_found(line_before[idx - 1], line[idx])
		|| gap_found(line_before[idx], line[idx])
		|| gap_found(line_before[idx + 1], line[idx]))
	{
		ret = FALSE;
	}
	return (ret);
}

static void	update_map_width(size_t const width)
{
	t_map	*map;

	map = get_map_singleton();
	if (map->width < width)
		map->width = width;
}

static t_bool	tab_to_spaces(char **str)
{
	char	*dest;
	size_t	idx_str;
	size_t	idx_dest;

	dest = ft_malloc(ft_strlen(*str) + (ft_charcount(*str, '\t') * 3) + 1,
			sizeof(char));
	if (dest)
	{
		idx_str = 0;
		idx_dest = 0;
		while ((*str)[idx_str])
		{
			if ((*str)[idx_str] == '\t')
				idx_dest += 3;
			else
				dest[idx_dest] = (*str)[idx_str];
			idx_dest++;
			idx_str++;
		}
	}
	else
		ft_strerror(ALLOCATION_ERROR, ALLOCATION_FAILED);
	ft_free((void **)str);
	*str = dest;
	return (dest != NULL);
}

t_bool	is_line_valid(char const *line_before, char **line)
{
	t_bool	ret;
	size_t	idx;

	ret = TRUE;
	if (ft_strchr(*line, '\t'))
		ret = tab_to_spaces(line);
	idx = 0;
	while ((*line)[idx] && ret == TRUE)
	{
		if (!is_map_character((*line)[idx]) && (*line)[idx] != ' ')
		{
			ft_strerror(INVALID_ARGUMENT, INVALID_MAP_CHARACTER);
			ret = FALSE;
		}
		else if (!is_map_closed(line_before, *line, idx))
		{
			ft_strerror(INVALID_ARGUMENT, MAP_WALL_INCOMPLETE);
			ret = FALSE;
		}
		idx++;
	}
	update_map_width(idx);
	return (ret);
}
