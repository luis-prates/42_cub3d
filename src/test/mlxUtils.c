/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:20:43 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/01 18:15:01 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*new_mlx_connection(void)
{
	void	*mlx_connection;

	mlx_connection = mlx_init();
	if (!mlx_connection)
		ft_strerror(ALLOCATION_ERROR, MLX_CONNECTION_ERROR, NULL);
	return (mlx_connection);
}

void	free_mlx_connection(void **mlx_connection)
{
	if (!mlx_connection || !(*mlx_connection))
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, NULL);
	ft_free(mlx_connection);
}

void	*new_mlx_window(t_dinodude *game_info,
			int size_x, int size_y, char *title)
{
	void	*mlx_window;

	if (!(game_info->mlx_connection))
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, game_info);
	mlx_window = mlx_new_window(game_info->mlx_connection,
			size_x, size_y, title);
	if (!mlx_window)
		ft_strerror(ALLOCATION_ERROR, MLX_WINDOW_CREATION_ERROR, game_info);
	return (mlx_window);
}

void	free_mlx_window(void *mlx_connection, void **mlx_window)
{
	if (!mlx_connection)
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, NULL);
	if (*mlx_window)
		mlx_destroy_window(mlx_connection, *mlx_window);
	*mlx_window = NULL;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
