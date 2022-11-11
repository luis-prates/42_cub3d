/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:57 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 21:31:46 by lprates          ###   ########.fr       */
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

t_bool	check_duplicate_keys(t_identifier const type)
{
	t_map		*map;

	map = get_map_singleton();
	if (type == NORTH)
		return (!map->no_assigned);
	if (type == SOUTH)
		return (!map->so_assigned);
	if (type == WEST)
		return (!map->we_assigned);
	if (type == EAST)
		return (!map->ea_assigned);
	if (type == CEILING)
		return (!map->ceil_assigned);
	if (type == FLOOR)
		return (!map->floor_assigned);
	return (TRUE);
}

static void	assign_textures(t_identifier const type, t_mlximage	texture)
{
	t_map		*map;

	map = get_map_singleton();
	if (type == NORTH && !map->no_assigned)
	{
		map->textures.north = texture;
		map->no_assigned = TRUE;
	}
	else if (type == SOUTH)
	{
		map->textures.south = texture;
		map->so_assigned = TRUE;
	}
	else if (type == WEST)
	{
		map->textures.west = texture;
		map->we_assigned = TRUE;
	}
	else if (type == EAST)
	{
		map->textures.east = texture;
		map->ea_assigned = TRUE;
	}
}

t_bool	convert_texture(t_identifier const type, char const *line)
{
	t_bool		ret;
	t_mlximage	texture;


	ret = check_duplicate_keys(type);
	if (ret)
		texture = get_texture(line);
	else
		ft_strerror(BAD_INPUT, DUPLICATE_KEYS);
	if (texture.img && ret)
		assign_textures(type, texture);
	else
		ret = FALSE;
	return (ret);
}
