/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 21:10:51 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_valid_cub_extention(char const *filename)
{
	t_bool	ret;
	ssize_t	idx_extention;

	ret = TRUE;
	idx_extention = ft_strlen(filename) - 4;
	if (idx_extention < 1
		|| ft_strncmp(&filename[idx_extention], ".cub", 5) != 0)
	{
		ft_strerror(INVALID_ARGUMENT, BAD_FILE_EXTENTION);
		ret = FALSE;
	}
	return (ret);
}

t_bool	are_textures_n_colours_parsed(void)
{
	t_map	*map;

	map = get_map_singleton();
	return (map->textures.north.img
		&& map->textures.south.img
		&& map->textures.west.img
		&& map->textures.east.img
		&& map->colours.celling != -1
		&& map->colours.floor != -1);
}

char const	*skip_spaces(char const *str)
{
	if (str)
	{
		while (*str && ft_isblank(*str))
			str++;
	}
	return (str);
}

t_identifier	get_identifier_type(char const *line)
{
	line = skip_spaces(line);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "NO\t", 3))
		return (WEST);
	else if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "SO\t", 3))
		return (EAST);
	else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "WE\t", 3))
		return (NORTH);
	else if (!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "EA\t", 3))
		return (SOUTH);
	else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "C\t", 2))
		return (CEILING);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "F\t", 2))
		return (FLOOR);
	else if (*line && is_map_character(*line))
		return (MAP);
	else if (!*line)
		return (SPACE);
	return (INVALID);
}

char const	*get_identifier_description(char const *line)
{
	char const	*description;
	char const	*temp;

	description = NULL;
	temp = line;
	temp = skip_spaces(temp);
	while (temp && ft_isalpha(*temp))
		temp++;
	temp = skip_spaces(temp);
	if (*temp)
	{
		description = temp;
		while (*temp && !ft_isblank(*temp))
			temp++;
		description = ft_substr(line, description - line, temp - description);
		while (*temp && ft_isblank(*temp))
			temp++;
		if (*temp)
			ft_free((void **)&description);
	}
	return (description);
}
