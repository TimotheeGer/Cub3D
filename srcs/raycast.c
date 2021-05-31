/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:41:22 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/31 16:08:49 by tigerber         ###   ########.fr       */
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
	double moveSpeed =  0.5; //the constant value is in squares/second
  double rotSpeed = 0.08; //the constant value is in radians/second

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
      if(data->par.map[(int)(data->x)][(int)(data->y + data->planeY * moveSpeed)] == '0')
        data->y += data->planeY * moveSpeed;
	}
	if (keycode == 'a')
	{
			if(data->par.map[(int)(data->x - data->planeX * moveSpeed)][(int)(data->y)] == '0')
        data->x -= data->planeX * moveSpeed;
      if(data->par.map[(int)(data->x)][(int)(data->y - data->planeY * moveSpeed)] == '0')
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
    int x = 0;
    int w = data->par.Rx;
    int h = data->par.Ry;
    
        //calculate ray position and direction
      

    for(int y = h / 2 + 1; y < h; ++y)
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
      float rayDirX0 = data->dx - data->planeX;
      float rayDirY0 = data->dy - data->planeY;
      float rayDirX1 = data->dx + data->planeX;
      float rayDirY1 = data->dy + data->planeY;
      // Current y position compared to the center of the screen (the horizon)
      int p = y - h / 2;

      float posZ = 0.5 * h;

      float rowDistance = posZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / w;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / w;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = data->x + rowDistance * rayDirX0;
      float floorY = data->y + rowDistance * rayDirY0;

      for(int x = 0; x < w; ++x)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        // get the texture coordinate from the fractional part
        int tx = (int)( data->par.textsol.widthtex * (floorX - cellX)) & (data->par.textsol.widthtex - 1);
        int ty = (int)(data->par.textsol.heigthtex * (floorY - cellY)) & (data->par.textsol.heigthtex - 1);

        floorX += floorStepX;
        floorY += floorStepY;

        int i = ty * data->par.textsol.line_lengthtex + tx * 4;
        int color;
        color = create_trgb(0, (int)(unsigned char)data->par.textsol.addrtex[i + 2],
                                    (int)(unsigned char)data->par.textsol.addrtex[i + 1],
                                    (int)(unsigned char)data->par.textsol.addrtex[i]); 
        my_mlx_pixel_put(&data->background, x, y, color);
      }
    }
    // x = 0;
    while (x<w)
    {
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
      
      //texturing calculations
          //calculate value of wallX
      double wallX; //where exactly the wall was hit
      double step = 1.0 * 512 / lineHeight;
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      if(side == 0)
          wallX = data->y + perpWallDist * rayDirY;
      else
          wallX = data->x + perpWallDist * rayDirX;
      wallX -= floor((wallX));
      
      int texX = (int)(wallX * (double)512);
      if(side == 0 && rayDirX > 0)
          texX = 512 - texX - 1;
      if(side == 1 && rayDirY < 0)
          texX = 512 - texX - 1;
      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      // Starting texture coordinate
      for(int y = drawStart ; y <= drawEnd; y++)
      {
          int texY = (int)texPos & (512 - 1);
          texPos += step;
          int i = texY * 2048 + texX * 4;
          int color = 0;
          if (y < h && x < w)
          {
              if (side == 0 && rayDirX < 0) // nord
              {
                color = create_trgb(0, (int)(unsigned char)data->par.textNO.addrtex[i + 2],
                                    (int)(unsigned char)data->par.textNO.addrtex[i + 1],
                                    (int)(unsigned char)data->par.textNO.addrtex[i]); 
              }
              if (side == 0 && rayDirX > 0) // sud
              {
                 color = create_trgb(0, (int)(unsigned char)data->par.textSO.addrtex[i + 2],
                                    (int)(unsigned char)data->par.textSO.addrtex[i + 1],
                                    (int)(unsigned char)data->par.textSO.addrtex[i]); 
              }
              if (side == 1 && rayDirY > 0) // east
              {
                color = create_trgb(0, (int)(unsigned char)data->par.textEA.addrtex[i + 2],
                                    (int)(unsigned char)data->par.textEA.addrtex[i + 1],
                                    (int)(unsigned char)data->par.textEA.addrtex[i]); 
              }
              if (side == 1 && rayDirY < 0) //west
              {
                color = create_trgb(0, (int)(unsigned char)data->par.textWE.addrtex[i + 2],
                                    (int)(unsigned char)data->par.textWE.addrtex[i + 1],
                                    (int)(unsigned char)data->par.textWE.addrtex[i]); 
              }
              my_mlx_pixel_put(&data->background, x, y, color);
          }
      }
      x++;
    }
      
}