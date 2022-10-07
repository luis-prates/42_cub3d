/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:42:20 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 04:24:28 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	convert_identifier(int fd, t_identifier type, char const *line)
{
	t_bool ret;

	ret = FALSE;
	if (is_texture_identifier(type))
		ret = convert_texture(type, line);
	else if (is_colour_identifier(type))
		ret = convert_colour(type, line);
	else if (type == MAP && are_textures_n_colours_parsed())
		ret = convert_map(fd, line);
	else
		ft_strerror(INVALID_ARGUMENT, MISSING_IDENTIFIERS_BEFORE_MAP);
	return (ret);
}

static t_bool	fill_map_n_player(int const fd)
{
	t_bool			ret;
	char			*line;
	t_identifier	type;
	ssize_t			rd;

	ret = TRUE;
	rd = 1;
	while (rd > FD_EOF && ret == TRUE)
	{
		rd = get_next_line(fd, &line);
		type = get_identifier_type(line);
		if (type == INVALID)
		{
			ft_strerror(INVALID_ARGUMENT, INVALID_IDENTIFIER);
			ret = FALSE;
		}
		else if (type != SPACE)
		{
			ret = convert_identifier(fd, type, line);
		}
		ft_free((void **)&line);
	}
	return (ret);
}

static t_bool	convert_file(char const *filename)
{
	t_bool	ret;
	int		fd;

	ret = FALSE;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_strerror(BAD_FILE_DESCRIPTOR, FILE_OPEN_ERROR);
	}
	else
	{
		ret = fill_map_n_player(fd);
		close(fd);
	}
	return (ret);
}

t_bool	parse_map(char const *filename)
{
	t_bool	ret;

	ret = FALSE;
	if (is_valid_cub_extention(filename))
	{
		ret = convert_file(filename);
	}
	return (ret);
}
