/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:41:22 by tigerber          #+#    #+#             */
/*   Updated: 2021/07/06 13:43:05 by tigerber         ###   ########.fr       */
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

//##############################################################################

//dessine les lisgne vertical//

void	drawverticalline(t_data *data, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		my_mlx_pixel_put(&data->screen, x, drawstart, color);
		drawstart++;
	}
}

//###############################################################################
void    init_floor_one(t_data *d)
{
    d->f.x = 0;
    d->f.raydirx0 = d->dx - d->planeX;
    d->f.raydiry0 = d->dy - d->planeY;
    d->f.raydirx1 = d->dx + d->planeX;
    d->f.raydiry1 = d->dy + d->planeY;
    d->f.p = d->f.y - d->par.Ry / 2;
    d->f.posz = 0.5 * d->par.Ry;
    d->f.rowdistance = d->f.posz / d->f.p;
    d->f.floorstepx = d->f.rowdistance * (d->f.raydirx1 - d->f.raydirx0) / d->par.Rx;
    d->f.floorstepy = d->f.rowdistance * (d->f.raydiry1 - d->f.raydiry0) / d->par.Rx;
    d->f.floorx = d->x + d->f.rowdistance * d->f.raydirx0;
    d->f.floory = d->y + d->f.rowdistance * d->f.raydiry0;
}

void    ft_floor(t_data *d)
{
    d->f.y = d->f.h / 2 + 1;
    while (d->f.y < d->par.Ry)
    {
      d->f.y++;
      init_floor_one(d);
      while( d->f.x < d->par.Rx)
      { 
        d->f.x++;
        int cellX = (int)(d->f.floorx);
        int cellY = (int)(d->f.floory);
        int tx = (int)( d->par.t_f.width * (d->f.floorx - cellX)) & (d->par.t_f.width - 1);
        int ty = (int)(d->par.t_f.heigth * (d->f.floory - cellY)) & (d->par.t_f.heigth - 1);
        d->f.floorx += d->f.floorstepx;
        d->f.floory += d->f.floorstepy;
        int i = ty * d->par.t_f.line_len + tx * 4;
        int color;
        color = create_trgb(0, (int)(unsigned char)d->par.t_f.addr[i + 2],
                                    (int)(unsigned char)d->par.t_f.addr[i + 1],
                                    (int)(unsigned char)d->par.t_f.addr[i]); 
        my_mlx_pixel_put(&d->screen, d->f.x, d->f.y, color);  
      } 
    }
}

void	init_raycast_part_one(t_data *d)
{
	d->r.cameraX = 2.0 * d->r.x / (double)d->r.w - 1.0;
	d->r.rayDirX = d->dx + d->planeX * d->r.cameraX;
    d->r.rayDirY = d->dy + d->planeY * d->r.cameraX;
    d->r.mapX = (int)d->x;
    d->r.mapY = (int)d->y;
    d->r.sideDistX = 0;
    d->r.sideDistY = 0;
    d->r.deltaDistX = fabs(1 / d->r.rayDirX);
    d->r.deltaDistY = fabs(1 / d->r.rayDirY);
    d->r.perpWallDist = 0;
    d->r.stepX = 0;
    d->r.stepY = 0;
    d->r.hit = 0;
    d->r.side = 0;
}

void	raycast_part_two(t_data *d)
{
	if(d->r.rayDirX < 0)
      {
        d->r.stepX = -1;
        d->r.sideDistX = (d->x - d->r.mapX) * d->r.deltaDistX;
      }
      else
      {
        d->r.stepX = 1;
        d->r.sideDistX = (d->r.mapX + 1.0 - d->x) * d->r.deltaDistX;
      }
      if(d->r.rayDirY < 0)
      {
        d->r.stepY = -1;
        d->r.sideDistY = (d->y - d->r.mapY) * d->r.deltaDistY;
      }
      else
      {
        d->r.stepY = 1;
        d->r.sideDistY = (d->r.mapY + 1.0 - d->y) * d->r.deltaDistY;
      }
}

void    raycaster(t_data *data)
{
    data->r.x = 0;
    data->r.w = data->par.Rx;
    data->r.h = data->par.Ry;

    ft_floor(data);

    while (data->r.x < data->r.w)
    {
		init_raycast_part_one(data);
		raycast_part_two(data);
    	while (hit == 0)
      	{ 
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
        if (data->par.map[mapX][mapY] == '1') 
          hit = 1;
      }
      if(side == 0)
      {
        perpWallDist = (mapX - data->x + (1 - stepX) / 2) / rayDirX;
      }
      else
        perpWallDist = (mapY - data->y + (1 - stepY) / 2) / rayDirY;

      int lineHeight = (int)(h / perpWallDist);

      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;
      
      double wallX;
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
                color = create_trgb(0, (int)(unsigned char)data->par.t_no.addr[i + 2],
                                    (int)(unsigned char)data->par.t_no.addr[i + 1],
                                    (int)(unsigned char)data->par.t_no.addr[i]); 
              }
              if (side == 0 && rayDirX > 0) // sud
              {
                 color = create_trgb(0, (int)(unsigned char)data->par.t_so.addr[i + 2],
                                    (int)(unsigned char)data->par.t_so.addr[i + 1],
                                    (int)(unsigned char)data->par.t_so.addr[i]); 
              }
              if (side == 1 && rayDirY > 0) // east
              {
                color = create_trgb(0, (int)(unsigned char)data->par.t_ea.addr[i + 2],
                                    (int)(unsigned char)data->par.t_ea.addr[i + 1],
                                    (int)(unsigned char)data->par.t_ea.addr[i]); 
              }
              if (side == 1 && rayDirY < 0) //west
              {
                color = create_trgb(0, (int)(unsigned char)data->par.t_we.addr[i + 2],
                                    (int)(unsigned char)data->par.t_we.addr[i + 1],
                                    (int)(unsigned char)data->par.t_we.addr[i]); 
              }
              my_mlx_pixel_put(&data->screen, x, y, color);
          }
      }
      x++;
    }    
}