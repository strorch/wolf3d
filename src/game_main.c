/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:58:30 by mstorcha          #+#    #+#             */
/*   Updated: 2018/09/15 20:58:45 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
# include "math.h"

void	verLine(int **map_h, int x, int startPoint, int endPoint, int color)
{
	int *map;

	/**
	TODO: fix segf
	*/
	map = *map_h;
	for (int i = 0; i < startPoint; i++)
	{
		map[SCREEN_H * i + x] = 0xF6F6F6;
	}
	for (int i = startPoint; i < endPoint; i++)
	{
		map[SCREEN_H * i + x] = color;
	}
	for (int i = endPoint; i < SCREEN_W; i++)
	{
		map[SCREEN_H * i + x] = 0x804040;
	}
}

int		*get_pixels_map(t_game *game_h)
{
	clock_t start, end;
	double cpu_time_used;
	t_game game;
	t_user user;

	game = *game_h;
	start = clock();
	int *map = (int *)ft_memalloc(sizeof(int) * SCREEN_W * SCREEN_H);
	user = *game.user;

	double posX = user.cam.pos.x, posY = user.cam.pos.y;  //x and y start position
	// printf("%f %f\n", posX, posY);
	double dirX = user.cam.dir.x, dirY = user.cam.dir.y; //initial direction vector
	double planeX = user.cam.plane.x, planeY = user.cam.plane.y; //the 2d raycaster version of camera plane
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	int w = SCREEN_W;
	int h = SCREEN_H;

	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//which box of the map we're in
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
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
			//jump to next map square, OR in x-direction, OR in y-direction
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
			if (game.map.keys[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		//choose wall color
		int color;
		switch(game.map.keys[mapX][mapY])
		{
			case 1:  color = 0xff0000;  break; //red
			case 2:  color = 0x00ff00;  break; //green
			case 3:  color = 0x0000ff;  break; //blue
			case 4:  color = 0xffff00;  break; //white
			default: color = 0x00ffff;  break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(&map, x, drawStart, drawEnd, color);
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
/*
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
*/
	double moveSpeed = cpu_time_used * 5.0; //the constant value is in squares/second
	double rotSpeed = cpu_time_used * 3.0; //the constant value is in radians/second
	game.user->cam.mv_speed = moveSpeed;
	game.user->cam.rot_speed = rotSpeed;

	return map;
}