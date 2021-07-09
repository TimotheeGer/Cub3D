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

void	drawverticalline(t_data *data, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		my_mlx_pixel_put(&data->screen, x, drawstart, color);
		drawstart++;
	}
}

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

void	raycast_part_three(t_data *d)
{
	while (d->r.hit == 0)
	{ 
		if(d->r.sideDistX < d->r.sideDistY)
		{
	  		d->r.sideDistX += d->r.deltaDistX;
	  		d->r.mapX += d->r.stepX;
	  		d->r.side = 0;
		}
		else
		{
	  		d->r.sideDistY += d->r.deltaDistY;
	  		d->r.mapY += d->r.stepY;
	  		d->r.side = 1;
		}
		if (d->par.map[d->r.mapX][d->r.mapY] == '1') 
	  		d->r.hit = 1;
	}
	if(d->r.side == 0)
	{
		d->r.perpWallDist = (d->r.mapX - d->x + (1 - d->r.stepX) / 2) / d->r.rayDirX;
	}
	else
		d->r.perpWallDist = (d->r.mapY - d->y + (1 - d->r.stepY) / 2) / d->r.rayDirY;
}

void	init_raycast_part_two(t_data *d)
{
	d->r.lineHeight = (int)(d->r.h / d->r.perpWallDist);
	d->r.drawStart = -d->r.lineHeight / 2 + d->r.h / 2;
  	if(d->r.drawStart < 0)
		d->r.drawStart = 0;
  	d->r.drawEnd = d->r.lineHeight / 2 + d->r.h / 2;
  	if(d->r.drawEnd >= d->r.h)
		d->r.drawEnd = d->r.h - 1;
  	d->r.step = 1.0 * 512 / d->r.lineHeight;
  	d->r.texPos = (d->r.drawStart - d->r.h / 2 + d->r.lineHeight / 2) * d->r.step;
  	if(d->r.side == 0)
		d->r.wallX = d->y + d->r.perpWallDist * d->r.rayDirY;
  	else
		d->r.wallX = d->x + d->r.perpWallDist * d->r.rayDirX;
	d->r.wallX -= floor((d->r.wallX));
	d->r.texX = (int)(d->r.wallX * (double)512);
  	if(d->r.side == 0 && d->r.rayDirX > 0)
		d->r.texX = 512 - d->r.texX - 1;
	if(d->r.side == 1 && d->r.rayDirY < 0)
		d->r.texX = 512 - d->r.texX - 1;
}

void	init_raycast_part_three(t_data *d)
{
	d->r.texY = (int)d->r.texPos & (512 - 1);
	d->r.texPos += d->r.step;
	d->r.i = d->r.texY * 2048 + d->r.texX * 4;
	d->r.color = 0;
}

void	raycast_part_four(t_data *d)
{
	if (d->r.side == 0 && d->r.rayDirX < 0) // nord
	{
		d->r.color = create_trgb(0, (int)(unsigned char)d->par.t_no.addr[d->r.i + 2],
						(int)(unsigned char)d->par.t_no.addr[d->r.i + 1],
						(int)(unsigned char)d->par.t_no.addr[d->r.i]); 
	}
	if (d->r.side == 0 && d->r.rayDirX > 0) // sud
	{
		d->r.color = create_trgb(0, (int)(unsigned char)d->par.t_so.addr[d->r.i + 2],
						(int)(unsigned char)d->par.t_so.addr[d->r.i + 1],
						(int)(unsigned char)d->par.t_so.addr[d->r.i]); 
	}
	if (d->r.side == 1 && d->r.rayDirY > 0) // east
	{
		d->r.color = create_trgb(0, (int)(unsigned char)d->par.t_ea.addr[d->r.i + 2],
						(int)(unsigned char)d->par.t_ea.addr[d->r.i + 1],
						(int)(unsigned char)d->par.t_ea.addr[d->r.i]); 
	}
	if (d->r.side == 1 && d->r.rayDirY < 0) //west
	{
		d->r.color = create_trgb(0, (int)(unsigned char)d->par.t_we.addr[d->r.i + 2],
						(int)(unsigned char)d->par.t_we.addr[d->r.i + 1],
						(int)(unsigned char)d->par.t_we.addr[d->r.i]); 
	}
}

void    raycaster(t_data *d)
{
	d->r.x = 0;
	d->r.w = d->par.Rx;
	d->r.h = d->par.Ry;
	ft_floor(d);
	while (d->r.x < d->r.w)
	{
		init_raycast_part_one(d);
		raycast_part_two(d);
		raycast_part_three(d);
		init_raycast_part_two(d);
		d->r.y = d->r.drawStart;
		while (d->r.y <= d->r.drawEnd)
	  	{
			init_raycast_part_three(d);
			if (d->r.y < d->r.h && d->r.x < d->r.w)
			{
				raycast_part_four(d);
				my_mlx_pixel_put(&d->screen, d->r.x, d->r.y, d->r.color);
			}
			d->r.y++;
		}
		d->r.x++;
	}    
}
