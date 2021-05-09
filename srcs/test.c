/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/30 14:47:27 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1024
#define screenHeight 512
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

int		worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int mapX = 8, mapY = 8, mapS = 64;
int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

typedef struct	s_img
{
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
	int		color2;
	int		colormap1;

}				t_img;

typedef struct	s_data
{
	t_img   player;
	t_img   background;
	int 	i;
	int		j;
	float	y;
	float	x;
	float	dx;
	float	dy;
	float	a;
	int     refresh;
	int		color;
	int		color2;
	int		color3;
	int		colormap2;
	void	*mlx;
	void	*win;
	
}				t_data;

//##############################################################################

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//##############################################################################

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

//##############################################################################

int     add_shade(double distance, int color)
{
	int r;
	int g;
	int b;
	
	r = (get_r(color) >> 16) * distance;
	g = (get_g(color) >> 8) * distance;
	b = (get_b(color)) * distance;
	
	color = r << 16 | g << 8 | b;
	return (color);
}

//##############################################################################

int     get_opposite(int color)
{
	int r;
	int g;
	int b;
	
	r = 255 - (get_r(color) >> 16);
	g = 255 - (get_g(color) >> 8);
	b = 255 - (get_b(color));

	color = r << 16 | g << 8 | b;
	return (color);
}

//###############################################################################

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//###############################################################################

int		key_hook(int keycode, t_data *img)
{
	img->refresh = 1;
	if (keycode == 'a')
		{
			img->a-=0.1;
			if (img->a < 0)
			{
				img->a+=2 * PI;
			}
			img->dx = cos(img->a) * 5;
			img->dy = sin(img->a) * 5;
		}
	if (keycode == 'd')
			{
			img->a+=0.1;
			if (img->a > 2 * PI)
			{
				img->a-=2 * PI;
			}
			img->dx = cos(img->a) * 5;
			img->dy = sin(img->a) * 5;
		}
	if (keycode == 'w')
		{
			img->x+= img->dx;
			img->y+= img->dy;
		}
	if (keycode == 's')
		{
			img->x-= img->dx;
			img->y-= img->dy;
		}
	return (0);
}

//###############################################################################

int		move_mouse(int button, int x, int y, t_data *img)
{
	(void)button;
	(void)img;
	printf("%d, %d\n", x, y);
	return (0);
}

//###############################################################################

int		mouse_hook(int button, int y, int x, t_data *img)
{
	(void)button;
	(void)y;
	(void)x;
	//printf("button = %d\n", button);
	(void)img;
	return (0);
}

//###############################################################################

int		close(int keycode, t_data *img)
{
	(void)keycode;
	//if (keycode == 65307)
	//{
		mlx_destroy_window(img->mlx, img->win);
		exit(0);
	//}
	return (0);
}	

//##############################################################################

void	fill_img(t_img img, int c, int start, int stop)
{
	int *bytes;
	int *end;

	end = (void *)img.addr + stop * img.line_length;
	bytes = (int *)((void*)img.addr + start * img.line_length);
	while (bytes < end)
		*bytes++ = c;
}

//##############################################################################


void	drawPlayer2d(t_data *img, int size)
{
	int x2 =  -size;
	int y2 =  -size;
	
	while (y2 <= size)
	{
		while (x2 <= size)
		{
			my_mlx_pixel_put(&img->background, img->x + x2, img->y + y2, 0XFFFF00);
			x2++;
		}
		x2 =  -size;
		y2++;
	}
}

void	drawlineplayer(t_data *img)
{//(void)img;
	int x1 = img->x;
	int y1 = img->y;
	int x2 = x1 + img->dx * 5;
	int y2 = y1 + img->dy * 5;
	int dx = x2 - x1;
	int dy = y2 - y1;
	// printf("x2, y2 = %d, %d\n", x2, y2);
	// printf("x1, y1 = %d, %d\n", x1, y1);
	// if (x2 == x1 || x2 - 1 == x1)
	// {
	// 	while (y1 > y2)
	// 	{
	// 		my_mlx_pixel_put(&img->background, x1 , y1, 0x00FF00);
	// 		y1--;
	// 	}
	// 	while (y2 > y1)
	// 	{
	// 		my_mlx_pixel_put(&img->background, x1 , y1, 0x00FF00);
	// 		y2--;
	// 	}
	// }
	if (dx < 0) {
		x1 = x2;
		y1 = y2;
		x2 = img->x;
		y2 = img->y;
	}
	int x = x1;
	int y = 0;
	while (x < x2)
	{
		y = y1 + dy * (x - x1) / dx;
		my_mlx_pixel_put(&img->background, x , y, 0xFFFF00);
		x++;
	}
}

void	drawline(t_data *img, int x3, int y3, int x4, int y4)
{
	int x1 = x3;
	int y1 = y3;
	int x2 = x4;
	int y2 = y4;
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx < 0) {
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
		my_mlx_pixel_put(&img->background, x , y, 0x00FF00);
		x++;
	}
}

void	drawverticalline(t_data *img, int x, int y, int y2)
{
	while (y < y2)
	{
		my_mlx_pixel_put(&img->background, x , y, img->color3);
		my_mlx_pixel_put(&img->background, x + 1 , y, img->color3);
		my_mlx_pixel_put(&img->background, x - 1, y, img->color3);
		my_mlx_pixel_put(&img->background, x + 2, y, img->color3);
		my_mlx_pixel_put(&img->background, x - 2, y, img->color3);
		my_mlx_pixel_put(&img->background, x + 3, y, img->color3);
		my_mlx_pixel_put(&img->background, x - 3, y, img->color3);
		my_mlx_pixel_put(&img->background, x + 4, y, img->color3);
		my_mlx_pixel_put(&img->background, x - 4, y, img->color3);
		y++;
	}
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
} 

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
		
		//*************check vertical lines**************//
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
		//printf("x, y = %d, %d\n", (int)img->x, (int)img->y);
		//printf("rx, ry = %d, %d\n", (int)rx, (int)ry);
		drawline(img, img->x, img->y, rx, ry);
		//*******draw 3D line********//
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
		printf("x, y = %d, %f\n", r * 8 + 530, lineO);
		printf("x2, y2 = %d, %f\n", r * 8 + 530, lineH + lineO);
		printf("*******************************\n");
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

void	full_screen_grey(t_img *img)
{
	int x = 0;
	int y = 0;
	
	while (y < screenHeight)
	{
		while (x < screenWidth)
		{
			my_mlx_pixel_put(img, x, y, 0xC0C0C0);
			x++;
		}
		x = 0;
		y++;
	}
	
}

void	put_quad_map(t_img *img, int a, int b, int maxb)
{
	while (b < maxb)
	{
		my_mlx_pixel_put(img, a, b, img->colormap1);
		b++;
	}
}



void	drawMap(t_img *img)
{
	int x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;
	int xa = 0;

	img->colormap1 = 0x000000;

	while (y < mapY)
	{
		while (x < mapX)
		{
			if (map[y * mapX + x] == 1)
				img->colormap1 = 0xFFFFFF;
			else
				img->colormap1 = 0x000000;
			xo = x * mapS;
			yo = y * mapS;
			xa = 0 + xo + 1;
			while (xa <  mapS + xo - 1)
			{
				put_quad_map(img, xa, 0 + yo + 1, mapS + yo - 1);
				xa++;
			}
			x++;
		}
		x = 0;
		y++;
	}

}

//##############################################################################

int		render_next_frame(t_data *img)
{
	if (img->refresh)
	{
		//full_screen_grey(img);
	mlx_clear_window(img->mlx, img->win);
	full_screen_grey(&img->background);
	drawMap(&img->background);
	drawRays3D(img);
	drawlineplayer(img);
	mlx_put_image_to_window(img->mlx, img->win, img->background.img, 0, 0);
	drawPlayer2d(img, 4);
	
	}
	img->refresh = 0;
	return (0);
}

//##############################################################################

void	ft_init(t_data *img)
{
	img->x = 300;
	img->y = 300;
	img->color = create_trgb(0, 255, 255, 0);
	img->dx = cos(img->a) * 5;
	img->dy = sin(img->a) * 5;
	//drawPlayer(img);

}

int		main(void)
{
	t_data img;
	memset(&img, 0, sizeof(img));
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, screenWidth, screenHeight, "***Cub3D***");
	img.background.img = mlx_new_image(img.mlx, screenWidth, screenHeight);
	img.background.addr = mlx_get_data_addr(img.background.img, &img.background.bits_per_pixel, &img.background.line_length, &img.background.endian);
	mlx_put_image_to_window(img.mlx, img.win, img.background.img, 0, 0);
	//img.player.img = mlx_new_image(img.mlx, 8, 8);
	//img.player.addr = mlx_get_data_addr(img.player.img, &img.player.bits_per_pixel, &img.player.line_length, &img.player.endian);
	ft_init(&img);
	img.refresh = 1;
	mlx_hook(img.win, 2, 1L<<0, key_hook, &img);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}

//##############################################################################
// int     main(void)
// {
// 	// int		x = 0;
	
// 	// double	posX = 22; //position de depart x et y
// 	// double	posY = 12;
	
// 	// double	dirX = -1; //vecteur de direction initiale
// 	// double	dirY = 0;
	
// 	// double	planX = 0; //version 2D raycaster
// 	// double	planY = 0.66;
	
// 	// double	time = 0; // heure de l'image actuelle
// 	// double	oldtime = 0; // heure de l'image précédente
	
// 	// double	cameraX = 0;
// 	// double	rayDirX = 0;
// 	// double	rayDirY = 0;
	
// 	// int		mapX = posX;
// 	// int		mapY = posY;
// 	t_data	img;
	
// 	int     img_width = 250;
//     int     img_height = 250;

// 	img.color = create_trgb(0, 255, 255, 0);
// 	img.mlx = mlx_init();
// 	img.win = mlx_new_window(img.mlx, 500, 500, "***Cub3D***");
// 	//img.img = mlx_new_image(img.mlx, screenWidth, screenHeight);
// 	img.img = mlx_xpm_file_to_image(img.mlx, "mur_1.xpm", &img_width, &img_height);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
// 	// while (x < 'w')
// 	// {
// 	// 	cameraX = 2 * x / (double)'w' - 1; //coordonne camera
// 	// 	rayDirX = dirX + planeX * cameraX;
// 	// 	rayDirY = dirY + planeX * cameraX;
// 	// 	x++;
// 	// }
	
// 	//mlx_key_hook(img.win, key_hook, &img);
// 	//mlx_mouse_hook(img.win, mouse_hook, &img);
// 	//mlx_hook(img.win, 6, 1L<<6, move_mouse, &img);
// 	// mlx_hook(img.win, 3, 1L<<0, key_hook, &img);
// 	// mlx_loop_hook(img.mlx, render_next_frame, &img);
// 	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
// 	mlx_loop(img.mlx);
// 	return (0);
// }
