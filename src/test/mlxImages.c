/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxImages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:57:55 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/01 18:12:34 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlximage	xpm_to_mlx_image(t_dinodude *game_info, char *file)
{
	t_mlximage	mlx_image;

	mlx_image.image = mlx_xpm_file_to_image(game_info->mlx_connection,
			file, &(mlx_image.width), &(mlx_image.height));
	if (!(mlx_image.image))
		ft_strerror(ALLOCATION_ERROR, MLX_IMAGE_CREATION_ERROR, game_info);
	mlx_image.image_address = mlx_get_data_addr(mlx_image.image,
			&(mlx_image.bits_per_pixel), &(mlx_image.line_length),
			&(mlx_image.endian));
	return (mlx_image);
}

void	free_t_mlximage(void *mlx_connection, t_mlximage *mlx_image)
{
	if (!mlx_connection)
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, NULL);
	if (mlx_image->image)
		mlx_destroy_image(mlx_connection, mlx_image->image);
	ft_bzero((void *)mlx_image, sizeof(t_mlximage));
}

t_mlximage	free_and_xpm_to_mlx_image(t_dinodude *game_info,
				t_mlximage *mlx_image, char *file)
{
	if (!(game_info->mlx_connection))
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, game_info);
	free_t_mlximage(game_info->mlx_connection, mlx_image);
	*mlx_image = xpm_to_mlx_image(game_info, file);
	return (*mlx_image);
}

/*
t_mlximage	new_mlx_image(t_dinodude *game_info)
{
	t_mlximage	mlx_image;

	if (!(game_info->mlx_connection))
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, game_info);
	mlx_image.image = mlx_new_image(game_info->mlx_connection,
			WINDOW_SIZE_X, WINDOW_SIZE_Y);
	mlx_image.image_address = mlx_get_data_addr(mlx_image.image,
			&(mlx_image.bits_per_pixel), &(mlx_image.line_length),
			&(mlx_image.endian));
	return (mlx_image);
}

void	pixel_mlx_image_put(t_mlximage *mlx_image,
			int size_x, int size_y, int hexColor)
{
	char	*pixel;

	if (!mlx_image)
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, game_info);
	pixel = mlx_image->image_address
		+ (size_y * mlx_image->line_length
			+ size_x * (mlx_image->bits_per_pixel / 8));
	*(unsigned int *)pixel = hexColor;
}
*/
