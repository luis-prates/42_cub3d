/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:15:25 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/01 20:42:40 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_strerror(char *message, int index)
{
	printf("%s: %s\n", message, strerror(index));
	exit(1);
}

static int	*ft_strtoiarr(char *str)
{
	int		*iarr;
	size_t	idx_iarr;
	size_t	idx_str;

	idx_str = 0;
	while (ft_isblank(str[idx_str]))
		idx_str++;
	idx_iarr = idx_str;
	while (ft_isdigit(str[idx_iarr]))
		idx_iarr++;
	iarr = (int *)malloc((idx_iarr - idx_str) * sizeof(int));
	if (!iarr)
		return (NULL);
	idx_iarr = 0;
	while (ft_isdigit(str[idx_str]))
		iarr[idx_iarr++] = str[idx_str++] - '0';
	return (iarr);
}

static short	check_file_n_count_map_size(int fd, char *identifier, t_map *map)
{
	int		ret;
	ssize_t	rd;
	char	buf[2];

	ret = 1;
	rd = 1;
	ft_bzero((void *)&buf, sizeof(char * 2));
	while (rd > FD_EOF && ret != 0)
	{
		rd = read(fd, buf, 1);
		if (buf[0] != 0)
		{

		}
	}

	if (ft_strncmp(identifier, "NO", 3) == 0)
	else if (ft_strncmp(identifier, "SO", 3) == 0)
	else if (ft_strncmp(identifier, "WE", 3) == 0)
	else if (ft_strncmp(identifier, "EA", 3) == 0)
	else if (ft_strncmp(identifier, "F", 2) == 0)
	else if (ft_strncmp(identifier, "C", 2) == 0)
	else if (ft_strncmp(identifier, "", 2) == 0) // TODO	returns a number ( what when map? )

	ft_bzero((void *)&identifier, sizeof(char * 3));
	return (ret);
}


static short	check_file_n_count_map_size(int fd, t_map *map)
{
	int		ret;
	ssize_t	rd;
	char	buf[2];
	char	identifier[3];

	ret = 1;
	rd = 1;
	ft_bzero((void *)&buf, sizeof(char * 2));
	ft_bzero((void *)&identifier, sizeof(char * 3));
	while (rd > FD_EOF && ret != 0)
	{
		rd = read(fd, buf, 1);
		if (buf[0] != '\n')
		{
			if (identifier[0] == 0)
				identifier[0] = buf[0];
			else if (identifier[1] == 0) // TODO check is as already a valid identifier
				identifier[1] = buf[0];
			else
				ret = handle_n_reset_identifier(fd, identifier, map);
		}
	}
	return (ret);
}


static short	check_file_n_count_map_size(int fd, t_map *map)
{
	int		ret;
	ssize_t	rd;
	char	buf[2];
	char	identifier[3];

	ret = 1;
	rd = 1;
	ft_bzero((void *)&buf, sizeof(char * 2));
	ft_bzero((void *)&identifier, sizeof(char * 3));
	while (rd > FD_EOF && ret != 0)
	{
		rd = read(fd, buf, 1);
		if (buf[0] != '\n')
		{
			if (identifier[0] == 0)
				identifier[0] = buf[0];
			else if (identifier[1] == 0)
				identifier[1] = buf[0];
			else
				ret = handle_n_reset_identifier(fd, map);
		}
	}
	return (ret);
}

static short	convert_file_to_map_n_player(char *filename, t_map *map, t_player *player)
{
	int		ret;
	int		fd;

	ret = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_strerror(BAD_FILE_DESCRIPTOR, FILE_OPEN_ERROR);
	else
	{
		if (check_file_n_count_map_size(fd, map))
			ret = fill_map_n_player(fd, map, player);
		close(fd);
	}
	return (ret);
}

static short	is_valid_extention(char *filename)
{
	short	ret;
	ssize_t	idx_extention;

	ret = 1;
	idx_extention = ft_strlen(filename) - 4;
	if (idx_extention < 1 || ft_strncmp(&filename[idx_extention], ".cub", 5) != 0)
	{
		ft_strerror(INVALID_ARGUMENT, BAD_FILE_EXTENTION);
		ret = 0;
	}
	return (ret);
}

static short	parse_map(char *filename, t_map *map, t_player *player)
{
	short	ret;

	ret = 0;
	if (is_valid_extention(filename))
	{
		ret = convert_file_to_map_n_player(filename, map, player);
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	t_map		map; // TODO Improve variables position/use
	t_player	player;

	if (argc >= 2)
	{
		ft_bzero((void *)&map, sizeof(t_map));
		ft_bzero((void *)&player, sizeof(t_player));
		if (!parse_map(argv[1], &map, &player))
		{
			return (EXIT_FAILURE)
		}
		else
		{
			// start game
		}
	}
	return (EXIT_SUCCESS)
}
