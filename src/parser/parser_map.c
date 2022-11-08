/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:35:53 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/16 13:18:49 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_map_height(void)
{
	t_map	*map;

	map = get_map_singleton();
	map->height++;
}

static t_bool	fill_map(char const *first_line)
{
	t_bool	ret;
	t_map	*map;
	int		fd;

	ret = TRUE;
	map = get_map_singleton();
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_strerror(BAD_FILE_DESCRIPTOR, FILE_OPEN_ERROR);
		ret = FALSE;
	}
	else
	{
		if (skip_identifiers(fd, first_line))
		{
			ret = alloc_n_convert_map(fd, first_line);
		}
		close(fd);
	}
	return (ret);
}

static t_bool	check_n_get_map_size(int const fd, char const *first_line)
{
	t_bool		ret;
	char		*line_before;
	char		*line;
	ssize_t		rd;

	ret = TRUE;
	line = ft_strdup(first_line);
	if (!is_line_valid(NULL, &line))
		ret = FALSE;
	rd = 1;
	while (rd > FD_EOF && *line && ret == TRUE)
	{
		line_before = line;
		rd = get_next_line(fd, (char **)&line);
		if (!is_line_valid(line_before, &line)
			|| (!*line && !is_line_valid(NULL, &line_before)))
			ret = FALSE;
		ft_free((void **)&line_before);
		update_map_height();
	}
	if (rd == FD_EOF && !is_line_valid(NULL, &line))
		ret = FALSE;
	ft_free((void **)&line);
	return (ret);
}

t_bool	convert_map(int const fd, char const *line)
{
	t_bool		ret;
	t_player	*player;

	ret = FALSE;
	player = get_player_singleton();
	if (check_n_get_map_size(fd, line))
	{
		ret = fill_map(line);
		if (ret == TRUE && player->exists == FALSE)
		{
			ft_strerror(INVALID_ARGUMENT, MISSING_PLAYER);
			ret = FALSE;
		}
	}
	return (ret);
}
