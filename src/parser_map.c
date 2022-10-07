/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:35:53 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 06:39:55 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// static int	*ft_strtoiarr(char *str)
// {
// 	int		*iarr;
// 	size_t	idx_iarr;
// 	size_t	idx_str;

// 	idx_str = 0;
// 	while (ft_isblank(str[idx_str]))
// 		idx_str++;
// 	idx_iarr = idx_str;
// 	while (ft_isdigit(str[idx_iarr]))
// 		idx_iarr++;
// 	iarr = (int *)malloc((idx_iarr - idx_str) * sizeof(int));
// 	if (!iarr)
// 		return (NULL);
// 	idx_iarr = 0;
// 	while (ft_isdigit(str[idx_str]))
// 		iarr[idx_iarr++] = str[idx_str++] - '0';
// 	return (iarr);
// }

static t_bool	is_end_line_spaces(char const *line, size_t idx)
{
	t_bool	ret;

	ret = TRUE;
	while (line[idx] && ft_isspace(line[idx]))
		idx++;
	if (line[idx])
	{
		ret = FALSE;
	}
	return (ret);
}

static t_bool	gap_found(char const c1, char const c2)
{
	t_bool	char_as_space;
	t_bool	char_not_as_space;

	char_as_space = (ft_isspace(c1)
		&& (c2 == MAP_FLOOR
		|| c2 == MAP_NORTH
		|| c2 == MAP_SOUTH
		|| c2 == MAP_WEST
		|| c2 == MAP_EAST));
	char_not_as_space = ((c1 == MAP_FLOOR
		|| c1 == MAP_NORTH
		|| c1 == MAP_SOUTH
		|| c1 == MAP_WEST
		|| c1 == MAP_EAST)
		&& ft_isspace(c2));
	return (char_as_space || char_not_as_space);
}

static t_bool	is_map_closed(char const *line_before, char const *line, size_t const idx)
{
	t_bool	ret;

	ret = TRUE;
	if (idx <= 0 || !line_before || ft_strlen(line_before) <= idx || !line[idx + 1])
	{
		if (gap_found(' ', line[idx]))
			ret = FALSE;
	}
	else if (gap_found(line[idx - 1], line[idx])
		|| gap_found(line_before[idx - 1], line[idx])
		|| gap_found(line_before[idx], line[idx]))
	{
		ret = FALSE;
	}
	return (ret);
}

static void		update_map_size(size_t const width)
{
	t_map	*map;

	map = get_map_singleton();
	if (map->width < width)
		map->width = width;
	map->height++;
}

static t_bool	is_line_valid(char const *line_before, char const *line)
{
	t_bool	ret;
	size_t	idx;

	ret = TRUE;
	idx = 0;
	while (ft_isspace(line[idx]))
		idx++;
	while (line[idx] && ret == TRUE)
	{
		if (!is_map_character(line[idx]) && !is_end_line_spaces(line, idx))
		{
			ft_strerror(INVALID_ARGUMENT, INVALID_MAP_CHARACTER);
			ret = FALSE;
		}
		else if (!is_map_closed(line_before, line, idx))
		{
			ft_strerror(INVALID_ARGUMENT, MAP_WALL_INCOMPLETE);
			ret = FALSE;
		}
		idx++;
	}
	update_map_size(idx);
	return (ret);
}

static t_bool	check_n_get_map_size(int const fd, char const *first_line)
{
	t_bool		ret;
	char const	*line_before;
	char const	*line;
	ssize_t		rd;

	ret = TRUE;
	line = ft_strdup(first_line);
	if (!is_line_valid(NULL, line))
	{
		ret = FALSE;
	}
	rd = 1;
	while (rd > FD_EOF && ret == TRUE)
	{
		line_before = line;
		rd = get_next_line(fd, (char **)&line);
		if (!is_line_valid(line_before, line))
		{
			ret = FALSE;
		} // TODO Map as last
		ft_free((void **)&line_before);
	}
	ft_free((void **)&line);
	return (ret);
}

t_bool	convert_map(int fd, char const *const line)
{
	t_bool		ret;

	ret = FALSE;
	if (check_n_get_map_size(fd, line))
	{
		ret = TRUE;
	}
	return (ret);
}
