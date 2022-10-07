/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 01:23:03 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char const **str)
{
	if (str && *str)
	{
		while (**str && ft_isspace(**str))
			(*str)++;
	}
}

t_identifier	get_identifier_type(char const *line)
{
	skip_spaces(&line);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NORTH);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SOUTH);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WEST);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EAST);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEILING);
	else if (ft_strncmp(line, "F ", 2) == 0)
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
	skip_spaces(&temp);
	temp += 2;
	skip_spaces(&temp);
	if (*temp)
	{
		description = temp;
		while (*temp && !ft_isspace(*temp))
			temp++;
		description = ft_substr(line,  description - line, temp - description);
		while (*temp && ft_isspace(*temp))
			temp++;
		if (*temp)
			ft_free((void **)&description);
	}
	return (description);
}
