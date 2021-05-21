/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawRay3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:48:20 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/21 13:09:10 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1080
#define screenHeight 920
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

int mapX = 24, mapY = 24, mapS = 10;
int map[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1,
  	1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,
  	1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

float	dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	drawline(t_data *data, int x3, int y3, int x4, int y4)
{
	int x1 = x3;
	int y1 = y3;
	int x2 = x4;
	int y2 = y4;
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx < 0)
	{
		x1 = x2;
		y1 = y2;
		x2 = x3;
		y2 = y3;
	}
	int x = x1;
	int y = 0;
	while (x < x2)
	{
		y = y1 + dy * (x - x1) / dx;
		my_mlx_pixel_put(&data->background, x , y, 0x00FF00);
		x++;
	}
}

void	drawRays3D(t_data *data)
{
	int 	r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, disT;
	float	aTan = 0;
	float	nTan = 0;
	float	disH = 0;
	float	disV = 0;

	ra = data->a - DR * 30;
	if (ra < 0) 
	{
		ra += 2 * PI;
	}
	if (ra > 2 * PI)
	{
		ra -= 2 * PI;
	}
	r = 0;
	
	while (r < 60) 
	{	
		//**************check horizontal lines**************//
		dof = 0;
		disH = 1000000;
		float hx = data->x;
		float hy = data->y;
		aTan = -1 / tan(ra);
		//****************************************************//
		if (ra > PI)
		{
			ry = (((int)data->y >> 6) <<6) - 0.0001;
			rx = (data->y - ry) * aTan + data->x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)data->y >> 6) <<6) + 64;
			rx = (data->y - ry) * aTan + data->x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->x;
			ry = data->y;
			dof = 8;
		}
		//****************************************************//
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * mapX + mx;
			
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				disH = dist(data->x, data->y, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// drawline(data, data->x, data->y, rx, ry);
		//****************************************check vertical lines*****************************//
		dof = 0;
		disV = 1000000;
		float vx = data->x;
		float vy = data->y;
		nTan = -tan(ra);
		
		if (ra > P2 && ra < P3)
		{
			rx = (((int)data->x >> 6) <<6) - 0.0001;
			ry = (data->x - rx) * nTan + data->y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)data->x >> 6) <<6) + 64;
			ry = (data->x - rx) * nTan + data->y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->x;
			ry = data->y;
			dof = 8;
		}
		
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * mapX + mx;
			if ((mp > 0) && (mp < mapX * mapY) && (map[mp] == 1))
			{
				vx = rx;
				vy = ry;
				disV = dist(data->x, data->y, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
			data->color3 = 0xFF0000;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			data->color3 = 0xDC143C;
		}
		//****************************************************//
		// printf("x, y = %d, %d\n", (int)data->x, (int)data->y);
		// printf("rx, ry = %d, %d\n", (int)rx, (int)ry);
		drawline(data, data->x, data->y, rx, ry);
		//***************************************draw 3D line*********************************************//
		float	ca = data->a - ra;
		
		if (ca < 0)
		{
			ca += 2 * PI;
		}
		if (ca > 2 * PI)
		{
			ca -= 2 * PI;
		}

		disT = disT * cos(ca);
		float	lineH = (mapS * 320) / disT;

		if (lineH > 320)
		{
			lineH = 320;
		}

		float	lineO = 160 - lineH / 2;
	
		drawverticalline(data, r * 8 + 530, lineO, lineH + lineO, 0xFF0000);
		
		// printf("x, y = %d, %f\n", r * 8 + 530, lineO);
		// printf("x2, y2 = %d, %f\n", r * 8 + 530, lineH + lineO);
		// printf("*******************************\n");
		
		ra += DR;

		if (ra < 0) 
		{
			ra += 2 * PI;
		}
		if (ra > 2 * PI)
		{
			ra -= 2 * PI;
		}
		
		r++;
		}
}
