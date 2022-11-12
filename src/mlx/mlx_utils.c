/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:20:43 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 20:05:56 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*new_mlx_connection(void)
{
	void	*mlx_connection;

	mlx_connection = mlx_init();
	if (!mlx_connection)
		ft_strerror(ALLOCATION_ERROR, MLX_CONNECTION_ERROR);
	return (mlx_connection);
}

void	free_mlx_connection(void **mlx_connection)
{
	if (mlx_connection && *mlx_connection)
		mlx_destroy_display(*mlx_connection);
	ft_free(mlx_connection);
}

void	*new_mlx_window(int size_x, int size_y, char *title)
{
	t_mlx	*mlx;
	void	*mlx_window;

	mlx = get_mlx_singleton();
	mlx_window = NULL;
	if (mlx->connection)
	{
		mlx_window = mlx_new_window(mlx->connection, size_x, size_y, title);
		if (!mlx_window)
			ft_strerror(ALLOCATION_ERROR, MLX_WINDOW_CREATION_ERROR);
	}
	else
	{
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR);
	}
	return (mlx_window);
}

void	free_mlx_window(void **mlx_window)
{
	t_mlx	*mlx;

	if (mlx_window && *mlx_window)
	{
		mlx = get_mlx_singleton();
		if (mlx->connection)
		{
			mlx_destroy_window(mlx->connection, *mlx_window);
			*mlx_window = NULL;
		}
		else
		{
			ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR);
		}
	}
}
