/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:48:20 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/20 12:32:23 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	drawRays3D(t_data *img)
{
	int 	r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, disT;
	float	aTan = 0;
	float	nTan = 0;
	float	disH = 0;
	float	disV = 0;

	ra = img->a - DR * 30;
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
		float hx = img->x;
		float hy = img->y;
		aTan = -1 / tan(ra);
		//****************************************************//
		if (ra > PI)
		{
			ry = (((int)img->y >> 6) <<6) - 0.0001;
			rx = (img->y - ry) * aTan + img->x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)img->y >> 6) <<6) + 64;
			rx = (img->y - ry) * aTan + img->x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = img->x;
			ry = img->y;
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
				disH = dist(img->x, img->y, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// drawline(img, img->x, img->y, rx, ry);
		//****************************************check vertical lines*****************************//
		dof = 0;
		disV = 1000000;
		float vx = img->x;
		float vy = img->y;
		nTan = -tan(ra);
		
		if (ra > P2 && ra < P3)
		{
			rx = (((int)img->x >> 6) <<6) - 0.0001;
			ry = (img->x - rx) * nTan + img->y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)img->x >> 6) <<6) + 64;
			ry = (img->x - rx) * nTan + img->y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = img->x;
			ry = img->y;
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
				disV = dist(img->x, img->y, vx, vy, ra);
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
			img->color3 = 0xFF0000;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			img->color3 = 0xDC143C;
		}
		//****************************************************//
		// printf("x, y = %d, %d\n", (int)img->x, (int)img->y);
		// printf("rx, ry = %d, %d\n", (int)rx, (int)ry);
		drawline(img, img->x, img->y, rx, ry);
		//***************************************draw 3D line*********************************************//
		float	ca = img->a - ra;
		
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
	
		drawverticalline(img, r * 8 + 530, lineO, lineH + lineO);
		
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
