/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:15:25 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/07 12:58:58 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_strerror(int index, char const *message)
{
	printf("Error\n");
	printf("%s: %s\n", strerror(index), message);
}

int	main(int argc, char **argv)
{
	t_bool	ret;

	ret = EXIT_FAILURE;
	if (argc > 2)
	{
		ft_strerror(INVALID_ARGUMENT, MORE_THAN_ONE_MAP_GIVEN);
	}
	else if (argc == 2)
	{
		init_singletons();
		if (parse_map(argv[1]))
		{
			if (start_game()) // start game
				ret = EXIT_SUCCESS;
		}
		free_singletons();
	}
	else
	{
		ft_strerror(INVALID_ARGUMENT, FILE_NOT_PROVIDED);
	}
	return (ret);
}
