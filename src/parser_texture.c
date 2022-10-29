/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/08 03:35:08 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_valid_texture_file(char const *filepath)
{
	t_bool	ret;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		ret = FALSE;
		ft_strerror(BAD_FILE_DESCRIPTOR, TEXTURE_ERROR);
	}
	else
	{
		ret = TRUE;
		close(fd);
	}
	return (ret);
}

static t_mlximage	get_texture(char const *line)
{
	t_mlximage	texture;
	char const	*file;

	ft_bzero((void *)&texture, sizeof(t_mlximage));
	file = get_identifier_description(line);
	if (file)
	{
		if (is_valid_texture_file(file))
			texture = xpm_to_mlx_image(file);
		ft_free((void **)&file);
	}
	else
	{
		ft_strerror(INVALID_ARGUMENT, INVALID_TEXTURE_DESCRIPTION);
	}
	return (texture);
}

t_bool	convert_texture(t_identifier const type, char const *line)
{
	t_bool		ret;
	t_map		*map;
	t_mlximage	texture;

	ret = FALSE;
	map = get_map_singleton();
	texture = get_texture(line);
	if (texture.img)
	{
		if (type == NORTH)
			map->textures.north = texture;
		else if (type == SOUTH)
			map->textures.south = texture;
		else if (type == WEST)
			map->textures.west = texture;
		else if (type == EAST)
			map->textures.east = texture;
		ret = TRUE;
	}
	return (ret);
}
