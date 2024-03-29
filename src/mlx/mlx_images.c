/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:57:55 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/07 17:02:15 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlximage	xpm_to_mlx_image(char const *file)
{
	t_mlx		*mlx;
	t_mlximage	image;

	ft_bzero((void *)&image, sizeof(t_mlximage));
	mlx = get_mlx_singleton();
	if (mlx->connection)
	{
		image.img = mlx_xpm_file_to_image(mlx->connection, (char *)file,
				&image.width, &image.height);
		if (image.img)
			image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
					&image.line_length, &image.endian);
		else
			ft_strerror(ALLOCATION_ERROR, MLX_IMAGE_CREATION_ERROR);
	}
	else
	{
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR);
	}
	return (image);
}

t_mlximage	new_mlx_image(int const width, int const height)
{
	t_mlx		*mlx;
	t_mlximage	image;

	ft_bzero((void *)&image, sizeof(t_mlximage));
	mlx = get_mlx_singleton();
	if (mlx->connection)
	{
		image.img = mlx_new_image(mlx->connection, width, height);
		if (image.img)
		{
			image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
					&image.line_length, &image.endian);
			image.width = width;
			image.height = height;
		}
		else
		{
			ft_strerror(ALLOCATION_ERROR, MLX_IMAGE_CREATION_ERROR);
		}
	}
	else
	{
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR);
	}
	return (image);
}

void	free_mlximage(t_mlximage *image)
{
	t_mlx	*mlx;

	if (image->img)
	{
		mlx = get_mlx_singleton();
		if (mlx->connection)
		{
			mlx_destroy_image(mlx->connection, image->img);
			ft_bzero((void *)image, sizeof(t_mlximage));
		}
		else
		{
			ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR);
		}
	}
}

int	get_image_pixel(t_mlximage *image, int x, int y)
{
	char	*dst;

	if (image->addr)
	{
		dst = image->addr
			+ (y * image->line_length + x * (image->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (-1);
}

void	pixel_mlx_image_put(t_mlximage *image,
			int const x, int const y, int const color)
{
	char	*dst;

	if (image->addr)
	{
		dst = image->addr
			+ (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
