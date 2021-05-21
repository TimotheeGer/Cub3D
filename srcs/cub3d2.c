/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:41:22 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/21 18:15:15 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define screenWidth 1080
#define screenHeight 920
#define mapWidth 24
#define mapHeight 24

// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

//###############################################################################

//dessine les lisgne vertical//

void	drawverticalline(t_data *data, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		my_mlx_pixel_put(&data->background, x, drawstart, color);
		drawstart++;
	}
}

//###############################################################################

int		key_hook2(int keycode, t_data *data)
{
	double moveSpeed =  0.2; //the constant value is in squares/second
  double rotSpeed = 0.05; //the constant value is in radians/second
	printf("keycode = %d\n", keycode);
	data->refresh = 1;
	if (keycode == 'w')
	{
			if(data->par.map[(int)(data->x + data->dx * moveSpeed)][(int)(data->y)] == '0')
        data->x += data->dx * moveSpeed;
      if(data->par.map[(int)data->x][(int)(data->y + data->dy * moveSpeed)] == '0')
       data->y += data->dy * moveSpeed;
	}
	if (keycode == 's')
	{
			if(data->par.map[(int)(data->x - data->dx * moveSpeed)][(int)(data->y)] == '0')
        data->x -= data->dx * moveSpeed;
      if(data->par.map[(int)(data->x)][(int)(data->y - data->dy * moveSpeed)] == '0')
        data->y -= data->dy * moveSpeed;
	}
  if (keycode == 'd')
	{
			if(data->par.map[(int)(data->x + data->planeX * moveSpeed)][(int)(data->y)] == '0')
        data->x += data->planeX * moveSpeed;
      if(data->par.map[(int)(data->x)][(int)(data->y + data->dy * moveSpeed)] == '0')
        data->y += data->planeY * moveSpeed;
	}
	if (keycode == 'a')
	{
			if(data->par.map[(int)(data->x - data->planeX * moveSpeed)][(int)(data->y)] == '0')
        data->x -= data->planeX * moveSpeed;
      if(data->par.map[(int)(data->x)][(int)(data->y - data->dy * moveSpeed)] == '0')
        data->y -= data->planeY * moveSpeed;
	}
	if (keycode == 65361)
	{
      		double oldDirX = data->dx;
      		data->dx = data->dx * cos(rotSpeed) - data->dy * sin(rotSpeed);
      		data->dy = oldDirX * sin(rotSpeed) + data->dy * cos(rotSpeed);
      		double oldPlaneX = data->planeX;
      		data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
      		data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
	}
	if (keycode == 65363)
	{
			double oldDirX = data->dx;
      		data->dx = data->dx * cos(-rotSpeed) - data->dy * sin(-rotSpeed);
      		data->dy = oldDirX * sin(-rotSpeed) + data->dy * cos(-rotSpeed);
      		double oldPlaneX = data->planeX;
      		data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
      		data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
	}

	return (0);
}

void    raycaster(t_data *data)
{
    // t_img *data;
    int x = 0;
    int w = data->par.Rx;
    int h = data->par.Ry;
    // data->x = 7, data->y = 8;  //x and y start position
    // data->dx = -1, data->dy = 0; //initial direction vector
    // data->planeX = 0, data->planeY = 0.66; //the 2d raycaster version of camera plane
    
    	printf("datax = %f\n", data->x);
    	printf("datay = %f\n", data->y);
    	printf("datadx = %f\n", data->dx);
    	printf("datady = %f\n", data->dy);

    while (x < w)
    {
        //calculate ray position and direction
      double cameraX = 2.0 * x / (double)w - 1.0; //x-coordinate in camera space
      double rayDirX = data->dx + data->planeX * cameraX;
      double rayDirY = data->dy + data->planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)data->x;
      int mapY = (int)data->y;

      //length of ray from current position to next x or y-side
      double sideDistX = 0;
      double sideDistY = 0;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist = 0;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX = 0;
      int stepY = 0;

      int hit = 0; //was there a wall hit?
      int side = 0; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (data->x - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->x) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (data->y - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->y) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
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
        if (data->par.map[mapX][mapY] == '1') 
          hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0)
      {
        perpWallDist = (mapX - data->x + (1 - stepX) / 2) / rayDirX;
      }
      else
        perpWallDist = (mapY - data->y + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

      //choose wall color
      int color;
      // switch(data->par.map[mapX][mapY])
      // {
      //   case 1:  color = create_trgb(125, 139,69,19);    break; //red
      //   case 2:  color = create_trgb(125, 160,82,45); break;//green
      //   case 3:  color = create_trgb(125, 210,105,30); break;//blue
      //   case 4:  color = create_trgb(125, 205,133,63); break;//white
      //   default: color = create_trgb(125, 244,164,96); break;//yellow
      // }
      if (data->par.map[mapX][mapY] == '1')
      {
        color = create_trgb(125, 139,69,19);
      }

      //give x and y sides different brightness
      if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      //verLine(x, drawStart, drawEnd, color);
      drawverticalline(data, x, drawStart, drawEnd, color);
      x++;
    }
    
}