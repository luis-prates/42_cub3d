/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/09/24 11:36:55 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include "cub3d.h"

/* The first ticks value of the application */
static struct timeval start;

void my_StartTicks(void)
{
	/* Set first ticks value */
	gettimeofday(&start, NULL);
}

__uint32_t	my_GetTicks (void)
{
	struct timeval now;
	__uint32_t ticks;

	gettimeofday(&now, NULL);
	ticks=(now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)/1000;
	return(ticks);
}

int	main(void)
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	t_vars	vars;
	t_data	img;
	my_StartTicks();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Ray Caster!");
	while (1)
	{
		img.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
		for(int x = 0; x < screenWidth; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double) screenWidth - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = (int) posX;
			int mapY = (int) posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirX == 0) ? INFINITY : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? INFINITY : fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			//Calculate height of line to draw on screen
			int lineHeight = (int) (screenHeight / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if (drawEnd >= screenHeight)
				drawEnd = screenHeight - 1;
			int color = create_trgb(0, 150, 218, 233);
			switch(worldMap[mapX][mapY])
			{
				case 1:  color = create_trgb(0, 150, 218, 233);  break;
				default: color = get_oposite(color); break;
			}
			//give x and y sides different brightness
			if (side == 1)
				color = color / 2;
			for (int i = drawStart; i < drawEnd; i++)
			{
				my_mlx_pixel_put(&img, x, i, color);
			}
		}
		//timing for input and FPS counter
		oldTime = time;
		time = my_GetTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		printf("%f", 1.0 / frameTime); //FPS counter
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		mlx_destroy_image(vars.mlx, img.img);

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

		//move forward if no wall in front of you
		if (0)
		{
			if (worldMap[(int) (posX + dirX * moveSpeed)][(int) posY] == 0)
				posX += dirX * moveSpeed;
			if (worldMap[(int) posX][(int) (posY + dirY * moveSpeed)] == 0)
				posY += dirY * moveSpeed;
		}
		//move backwards if no wall behind you
		if (0)
		{
			if (worldMap[(int) (posX - dirX * moveSpeed)][(int) posY] == 0)
				posX -= dirX * moveSpeed;
			if (worldMap[(int) posX][(int) (posY - dirY * moveSpeed)] == 0)
				posY -= dirY * moveSpeed;
		}
		//rotate to the right
		if (1)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		//rotate to the left
		if (0)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}
	}
}
