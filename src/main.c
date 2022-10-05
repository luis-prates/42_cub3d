/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:15:25 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/05 21:07:27 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_strerror(int index, char const *message)
{
	printf("%s: %s\n", message, strerror(index));
	exit(EXIT_FAILURE);
}

void	free_all(t_map *const map, t_player *player)
{
	// MAP
	ft_freemtx((void ***)&map->map);
	ft_free((void **)&map->textures.north);
	ft_free((void **)&map->textures.south);
	ft_free((void **)&map->textures.east);
	ft_free((void **)&map->textures.west);
	ft_free((void **)&map->colours.celling);
	ft_free((void **)&map->colours.floor);

	// PLAYER
	//ft_free((void **)&player->);
	player->direction = player->direction + 1; // todo remove
}

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

static bool	is_valid_texture_file(char const *filepath)
{
	bool	ret;
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

static bool convert_n_free_texture(short const identifier_type, char const *texture_path, t_map *map)
{
	bool	ret;
	int		fd;

	ret = FALSE;
	if (is_valid_texture_file(texture_path))
	{
		if (identifier_type == NORTH_IDENTIFIER)
			map->textures.north = ft_strdup(texture_path);
		else if (identifier_type == SOUTH_IDENTIFIER)
			map->textures.south = ft_strdup(texture_path);
		else if (identifier_type == WEST_IDENTIFIER)
			map->textures.west = ft_strdup(texture_path);
		else if (identifier_type == EAST_IDENTIFIER)
			map->textures.east = ft_strdup(texture_path);
		ret = TRUE;
	}
	ft_free((void **)&texture_path);
	return (ret);
}

static bool is_major_colour(int colour)
{
	return (colour >= 0 && colour <= 255);
}

static bool are_valid_colours(char const **const colours)
{
	bool	ret;
	short	idx_colour;
	size_t	str_len;
	size_t	colour_len;

	ret = TRUE;
	if (!colours[0] || !colours[1] || !colours[2])
		ret = FALSE;
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

static bool convert_string_to_major_colours(char const *str, int *const r, int *const g, int *const b)
{
	bool	ret;
	char	**colours;

	ret = FALSE;
	colours = ft_split(str, ',');
	if (are_valid_colours(colours))
	{
		*r = ft_atoi(colours[0]);
		*g = ft_atoi(colours[1]);
		*b = ft_atoi(colours[2]);
		ret = is_major_colour(*r) && is_major_colour(*g) && is_major_colour(*b);
	}
	ft_freemtx((void ***)&colours);
	return (ret);
}

static bool convert_n_free_colour(short const identifier_type, char *colour, t_map *map)
{
	bool	ret;
	int		r;
	int		g;
	int		b;

	ret = FALSE;
	if (convert_string_to_major_colours(colour, &r, &g, &b))
	{
		if (identifier_type == CEILING_IDENTIFIER)
			map->colours.celling = new_trgb(0, r, g, b);
		else if (identifier_type == FLOOR_IDENTIFIER)
			map->colours.floor = new_trgb(0, r, g, b);
		ret = TRUE;
	}
	ft_free((void **)&colour);
	return (ret);
}

static bool is_texture_identifier(short const identifier_type)
{
	return (identifier_type == NORTH_IDENTIFIER
		|| identifier_type == SOUTH_IDENTIFIER
		|| identifier_type == WEST_IDENTIFIER
		|| identifier_type == EAST_IDENTIFIER);
}

static bool is_colour_identifier(short const identifier_type)
{
	return (identifier_type == CEILING_IDENTIFIER
		|| identifier_type == FLOOR_IDENTIFIER);
}

static bool	convent_identifier(short const identifier_type, char const *line, t_map *map)
{
	bool ret;

	ret = FALSE;
	if (is_texture_identifier(identifier_type))
		ret = convert_n_free_texture(identifier_type, ft_substr(line, 3, ft_strlen(line) - 3), map);
	else if (is_colour_identifier(identifier_type))
		ret = convert_n_free_colour(identifier_type, ft_substr(line, 2, ft_strlen(line) - 2), map);
	return (ret);
}




static bool	convert_map(char const *line, t_map *map, t_player *player)
{
	bool ret;

	ret = FALSE;

	return (ret);
}



static bool	get_identifier_type_number(char const *identifier)
{
	if (ft_strncmp(identifier, "NO ", 3) == 0)
		return (NORTH_IDENTIFIER);
	else if (ft_strncmp(identifier, "SO ", 3) == 0)
		return (SOUTH_IDENTIFIER);
	else if (ft_strncmp(identifier, "WE ", 3) == 0)
		return (WEST_IDENTIFIER);
	else if (ft_strncmp(identifier, "EA ", 3) == 0)
		return (EAST_IDENTIFIER);
	else if (ft_strncmp(identifier, "C ", 2) == 0)
		return (CEILING_IDENTIFIER);
	else if (ft_strncmp(identifier, "F ", 2) == 0)
		return (FLOOR_IDENTIFIER);
	return (FALSE);
}

static bool	fill_map_n_player(int const fd, t_map *map, t_player *player)
{
	bool	ret;
	char	*line;
	short	identifier_type;
	ssize_t	rd;

	ret = TRUE;
	rd = 1;
	while (rd > FD_EOF && ret != 0)
	{
		rd = get_next_line(fd, &line); // TODO BUFFER MUST BE 1
		ft_strreplace(line, '\n', 0); // ?? really necessary ??
		if (line[0]) // ?? really necessary ?? when a line is only ´\n´
		{
			identifier_type = get_identifier_type_number(line);
			if (identifier_type)
				ret = convent_identifier(identifier_type, line, map);
			else
				ret = convert_map(line, map, player);
		}
		ft_free((void **)&line);
	}
	return (ret);
}

static bool	convert_file_to_map_n_player(char const *filename, t_map *map, t_player *player)
{
	bool	ret;
	int		fd;

	ret = FALSE;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_strerror(BAD_FILE_DESCRIPTOR, FILE_OPEN_ERROR);
	else
	{
		ret = fill_map_n_player(fd, map, player);
		close(fd);
	}
	return (ret);
}

static bool	is_valid_extention(char const *filename)
{
	bool	ret;
	ssize_t	idx_extention;

	ret = TRUE;
	idx_extention = ft_strlen(filename) - 4;
	if (idx_extention < 1 || ft_strncmp(&filename[idx_extention], ".cub", 5) != 0)
	{
		ft_strerror(INVALID_ARGUMENT, BAD_FILE_EXTENTION);
		ret = FALSE;
	}
	return (ret);
}

static bool	parse_map(char const *filename, t_map *map, t_player *player)
{
	bool	ret;

	ret = FALSE;
	if (is_valid_extention(filename))
	{
		ret = convert_file_to_map_n_player(filename, map, player);
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	bool	ret;
	t_map		map; // TODO Improve variables position/use
	t_player	player;

	ret = EXIT_FAILURE;
	if (argc > 2)
		ft_strerror(INVALID_ARGUMENT, MORE_THAN_ONE_MAP_GIVEN);
	if (argc == 2)
	{
		ft_bzero((void *)&map, sizeof(t_map));
		ft_bzero((void *)&player, sizeof(t_player));
		if (parse_map(argv[1], &map, &player))
		{
			// start game
			ret = EXIT_SUCCESS;
		}
	}
	else
		ft_strerror(INVALID_ARGUMENT, FILE_NOT_PROVIDED);
	free_all(&map, &player);
	return (ret);
}
