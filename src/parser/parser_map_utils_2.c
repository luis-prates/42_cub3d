/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:35:53 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/07 20:52:05 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	alloc_map_memory(void)
{
	t_bool	ret;
	t_map	*map;
	size_t	idx;

	ret = TRUE;
	map = get_map_singleton();
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	if (!map->map)
		ret = FALSE;
	idx = 0;
	while (idx < map->height && ret == TRUE)
	{
		map->map[idx] = ft_calloc(map->width, sizeof(int));
		if (!map->map)
			ret = FALSE;
		idx++;
	}
	if (ret == FALSE)
		ft_strerror(ALLOCATION_ERROR, ALLOCATION_FAILED);
	return (ret);
}

// can be with reverse var as used in oher function
// this was just to test
// for some reason the positions have to be reversed,
// same as the dir's. Most likely from math being done.
// Is it worth changing??
static void	save_player_position_n_direction(int pos_x, int pos_y, char dir)
{
	t_player	*player;

	player = get_player_singleton();
	player->pos.x = pos_y;
	player->pos.y = pos_x;
	if (dir == MAP_NORTH || dir == MAP_SOUTH)
	{
		player->dir.y = 0;
		player->dir.x = -1 + (dir == MAP_SOUTH) * 2;
		player->plane.x = 0;
		player->plane.y = 0.66 + (dir == MAP_SOUTH) * -1 * 1.32;
	}
	else if (dir == MAP_WEST || dir == MAP_EAST)
	{
		player->dir.y = -1 + (dir == MAP_EAST) * 2;
		player->dir.x = 0;
		player->plane.x = -0.66 + (dir == MAP_EAST) * 1.32;
		player->plane.y = 0;
	}
}

static void	line_to_int_array(char const *line, int *dest, int const pos_y)
{
	size_t	line_idx;
	size_t	dest_idx;

	line_idx = 0;
	dest_idx = 0;
	while (line[line_idx])
	{
		if (line[line_idx] == MAP_WALL)
			dest[dest_idx] = 1;
		else if (line[line_idx] == '\t')
			dest_idx += 3;
		else if (is_player_character(line[line_idx]))
			save_player_position_n_direction(dest_idx, pos_y, line[line_idx]);
		dest_idx++;
		line_idx++;
	}
}

t_bool	alloc_n_convert_map(int const fd, char const *first_line)
{
	t_bool		ret;
	t_map		*map;
	size_t		idx;
	char const	*line;
	ssize_t		rd;

	ret = alloc_map_memory();
	map = get_map_singleton();
	line_to_int_array(first_line, map->map[0], 0);
	idx = 1;
	rd = 1;
	while (rd > FD_EOF && idx < map->height && ret == TRUE)
	{
		rd = get_next_line(fd, (char **)&line);
		line_to_int_array(line, map->map[idx], idx);
		ft_free((void **)&line);
		idx++;
	}
	return (ret);
}

t_bool	skip_identifiers(int const fd, char const *first_line)
{
	t_bool		ret;
	size_t		first_line_length;
	char const	*line;
	ssize_t		rd;

	first_line_length = ft_strlen(first_line);
	rd = get_next_line(fd, (char **)&line);
	while (rd > FD_EOF
		&& ft_strncmp(first_line, line, first_line_length + 1) != 0)
	{
		ft_free((void **)&line);
		rd = get_next_line(fd, (char **)&line);
	}
	ret = ft_ternchar(rd > FD_EOF && *line, TRUE, FALSE);
	ft_free((void **)&line);
	return (ret);
}
