/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:41:22 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/25 12:46:43 by tigerber         ###   ########.fr       */
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
        int tx = (int)( d->par.t_sol.width * (d->f.floorx - cellX)) & (d->par.t_sol.width - 1);
        int ty = (int)(d->par.t_sol.heigth * (d->f.floory - cellY)) & (d->par.t_sol.heigth - 1);
        d->f.floorx += d->f.floorstepx;
        d->f.floory += d->f.floorstepy;
        int i = ty * d->par.t_sol.line_len + tx * 4;
        int color;
        color = create_trgb(0, (int)(unsigned char)d->par.t_sol.addr[i + 2],
                                    (int)(unsigned char)d->par.t_sol.addr[i + 1],
                                    (int)(unsigned char)d->par.t_sol.addr[i]); 
        my_mlx_pixel_put(&d->screen, d->f.x, d->f.y, color);  
      } 
    }
}



void    raycaster(t_data *data)
{
    int x = 0;
    int w = data->par.Rx;
    int h = data->par.Ry;

    ft_floor(data);

    while (x<w)
    {
      double cameraX = 2.0 * x / (double)w - 1.0;
      double rayDirX = data->dx + data->planeX * cameraX;
      double rayDirY = data->dy + data->planeY * cameraX;
      int mapX = (int)data->x;
      int mapY = (int)data->y;
      double sideDistX = 0;
      double sideDistY = 0;
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist = 0;
      int stepX = 0;
      int stepY = 0;
      int hit = 0;
      int side = 0;
      
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
    ft_sprite(data);
    
}