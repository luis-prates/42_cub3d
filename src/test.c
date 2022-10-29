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

#include "cub3d.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/* The first ticks value of the application */
static struct timeval start;

void my_startticks(void)
{
	/* Set first ticks value */
	gettimeofday(&start, NULL);
}

unsigned int	my_getticks(void)
{
	struct timeval		now;
	unsigned int		ticks;

	gettimeofday(&now, NULL);
	ticks = (now.tv_sec - start.tv_sec) * 1000 \
		+ (now.tv_usec - start.tv_usec) / 1000;
	return (ticks);
}

int		draw_image(t_mlx *all, int x, int color, t_draw draw)
{
	for (size_t j = 0; j < screenHeight; j++)
	{
		if (j < screenHeight / 2)
			my_mlx_pixel_put(&all->img, x, j, create_trgb(0, 0, 255, 0));
		if (j > screenHeight / 2)
			my_mlx_pixel_put(&all->img, x, j, create_trgb(0, 0, 0, 255));
	}
	//color = create_trgb(0, 255, 255, 0);
	/*for (int i = draw.draw_start; i < draw.draw_end; i++)
	{
		my_mlx_pixel_put(&all->img, x, i, color);
	}*/
}

/* static double posX = 22, posY = 12;  //x and y start position
** static double dirX = -1, dirY = 0; //initial direction vector
** planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
*/
int	render_next_frame(t_mlx *all)
{
	static double	time;
	static double	oldTime;
	t_draw			draw;
	//int				color;
	t_player		*player;
	void			*texture[8];
	__uint32_t		buffer[screenHeight][screenWidth];

	unsigned long tw, th;
	texture[0] = mlx_xpm_file_to_image(all->mlx, "./wall_textures/wall1.xpm", &tw, &th);
	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			/*texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture*/
		}
	player = player_singleton(NULL);
	new_image(all);
	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		draw.camera_x = 2 * x / (double) screenWidth - 1; //x-coordinate in camera space
		draw.ray_dir_x = player->dir_x + player->plane_x * draw.camera_x;
		draw.ray_dir_y = player->dir_y + player->plane_y * draw.camera_x;
		//which box of the map we're in
		draw.map_x = (int) player->pos_x;
		draw.map_y = (int) player->pos_y;

		//length of ray from current position to next x or y-side
		//double sideDistX;
		//double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		draw.delta_dist_x = (draw.ray_dir_x == 0) ? INFINITY : fabs(1 / draw.ray_dir_x);
		draw.delta_dist_y = (draw.ray_dir_y == 0) ? INFINITY : fabs(1 / draw.ray_dir_y);
		//double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		//int stepX;
		//int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (draw.ray_dir_x < 0)
		{
			draw.step_x = -1;
			draw.side_dist_x = (player->pos_x - draw.map_x) * draw.delta_dist_x;
		}
		else
		{
			draw.step_x = 1;
			draw.side_dist_x = (draw.map_x + 1.0 - player->pos_x) * draw.delta_dist_x;
		}
		if (draw.ray_dir_y < 0)
		{
			draw.step_y = -1;
			draw.side_dist_y = (player->pos_y - draw.map_y) * draw.delta_dist_y;
		}
		else
		{
			draw.step_y = 1;
			draw.side_dist_y = (draw.map_y + 1.0 - player->pos_y) * draw.delta_dist_y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (draw.side_dist_x < draw.side_dist_y)
			{
				draw.side_dist_x += draw.delta_dist_x;
				draw.map_x += draw.step_x;
				side = 0;
			}
			else
			{
				draw.side_dist_y += draw.delta_dist_y;
				draw.map_y += draw.step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[draw.map_x][draw.map_y] > 0)
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			draw.perp_wall_dist = (draw.side_dist_x - draw.delta_dist_x);
		else
			draw.perp_wall_dist = (draw.side_dist_y - draw.delta_dist_y);
		//Calculate height of line to draw on screen
		int lineHeight = (int) (screenHeight / draw.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		draw.draw_start = -lineHeight / 2 + screenHeight / 2;
		if (draw.draw_start < 0)
			draw.draw_start = 0;
		draw.draw_end = lineHeight / 2 + screenHeight / 2;
		if (draw.draw_end >= screenHeight)
			draw.draw_end = screenHeight - 1;

		int texNum = worldMap[draw.map_x][draw.map_y] - 1;

		double wallX;
		if (side == 0)
			wallX = player->pos_y + draw.perp_wall_dist * draw.ray_dir_y;
		else
			wallX = player->pos_x + draw.perp_wall_dist * draw.ray_dir_x;
		wallX -= floor(wallX);

		int texX = (int) (wallX * (double)texWidth);
		if (side == 0 && draw.ray_dir_x > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && draw.ray_dir_y < 0)
			texX = texWidth - texX - 1;
		//color = create_trgb(0, 255, 218, 0);
		/*switch(worldMap[draw.map_x][draw.map_y])
		{
			case 1:  color = create_trgb(100, 255, 255, 0);  break;
			default: color = get_oposite(color); break;
		}*/
		//give x and y sides different brightness
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (draw.draw_start - screenHeight / 2 + lineHeight / 2) * step;
		draw_image(all, x, 10, draw);
		for (int y = draw.draw_start; y < draw.draw_end; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			__uint32_t color = texture[0];
			if (side == 1)
				color = add_shade(0.6, color);
			buffer[y][x] = color;
			my_mlx_pixel_put(&all->img, x, y, color);
		}
	}
	mlx_put_image_to_window(all->mlx, all->win, texture[0], 0, 0);

	//timing for input and FPS counter
	oldTime = time;
	time = my_getticks();
	double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	//printf("%f\n", 1.0 / frameTime); //FPS counter
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_destroy_image(all->mlx, all->img.img);

	//speed modifiers
	double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

	//move forward if no wall in front of you
	if (player->movement == FORWARD)
	{
		if (worldMap[(int) (player->pos_x + player->dir_x * moveSpeed)][(int) player->pos_y] == 0)
			player->pos_x += player->dir_x * moveSpeed;
		if (worldMap[(int) player->pos_x][(int) (player->pos_y + player->dir_y * moveSpeed)] == 0)
			player->pos_y += player->dir_y * moveSpeed;
	}
	//move backwards if no wall behind you
	if (player->movement == BACKWARDS)
	{
		if (worldMap[(int) (player->pos_x - player->dir_x * moveSpeed)][(int) player->pos_y] == 0)
			player->pos_x -= player->dir_x * moveSpeed;
		if (worldMap[(int) player->pos_x][(int) (player->pos_y - player->dir_y * moveSpeed)] == 0)
			player->pos_y -= player->dir_y * moveSpeed;
	}
	//move left if no wall behind you
	if (player->movement == STRAFEL)
	{
		if (worldMap[(int) (player->pos_x - player->dir_y * moveSpeed)][(int) player->pos_y] == 0)
			player->pos_x -= player->dir_y * moveSpeed;
		if (worldMap[(int) player->pos_x][(int) (player->pos_y + player->dir_x * moveSpeed)] == 0)
			player->pos_y += player->dir_x * moveSpeed;
	}
	//move right if no wall behind you
	if (player->movement == STRAFER)
	{
		if (worldMap[(int) (player->pos_x + player->dir_y * moveSpeed)][(int) player->pos_y] == 0)
			player->pos_x += player->dir_y * moveSpeed;
		if (worldMap[(int) player->pos_x][(int) (player->pos_y - player->dir_x * moveSpeed)] == 0)
			player->pos_y -= player->dir_x * moveSpeed;
	}
	//rotate to the right
	if (player->movement == ROTR)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-rotSpeed) - player->dir_y * sin(-rotSpeed);
		player->dir_y = oldDirX * sin(-rotSpeed) + player->dir_y * cos(-rotSpeed);
		double oldPlaneX = player->plane_x;
		player->plane_x = player->plane_x * cos(-rotSpeed) - player->plane_y * sin(-rotSpeed);
		player->plane_y = oldPlaneX * sin(-rotSpeed) + player->plane_y * cos(-rotSpeed);
	}
	//rotate to the left
	if (player->movement == ROTL)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(rotSpeed) - player->dir_y * sin(rotSpeed);
		player->dir_y = oldDirX * sin(rotSpeed) + player->dir_y * cos(rotSpeed);
		double oldPlaneX = player->plane_x;
		player->plane_x = player->plane_x * cos(rotSpeed) - player->plane_y * sin(rotSpeed);
		player->plane_y = oldPlaneX * sin(rotSpeed) + player->plane_y * cos(rotSpeed);
	}
	printf("posx: %f, posy: %f dirx: %f diry: %f\n", player->pos_x, player->pos_y, player->dir_x, player->dir_y);
	return (0);
}

int	main(void)
{
	t_mlx		*all;
	t_player	*player;

	all = malloc(sizeof(t_mlx));
	player = malloc(sizeof(t_player));
	if (!all || !player)
	{
		printf("Error\nCouldn't allocate memory.");
		exit(-1);
	}
	//mlx_xpm_file_to_image
	all->mlx = 0;
	my_startticks();
	init_game(all, player);
	all = mlx_singleton(NULL);
	//mlx_key_hook(all->win, key_hook, all);
	mlx_hook(all->win, 2, (1L<<0), key_hook_press, all);
	mlx_hook(all->win, 3, (1L<<1), key_hook_release, all);
	mlx_loop_hook(all->mlx, render_next_frame, all);
	mlx_loop(all->mlx);
	return (0);
}
