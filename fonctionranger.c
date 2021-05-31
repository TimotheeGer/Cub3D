/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctionranger.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:46:45 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/27 13:54:01 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/cub3D.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1080
#define screenHeight 920
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

// int mapX = 24, mapY = 24, mapS = 10;
// int map[] =
// {
// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1,
//   	1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,
//   	1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//   	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
// };

//##############################################################################

//cree la couleur dans un int//

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//##############################################################################

//recupere la couleur//

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

//ajoute de lombre selon la distance//

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

//inverse la couleur//

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

//put un pixel//

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//###############################################################################

//a utiliser avec hook print la position de la souris//

int		move_mouse(int button, int x, int y, t_data *img)
{
	(void)button;
	(void)img;
	printf("%d, %d\n", x, y);
	return (0);
}

//###############################################################################

//print les boutton de la souris//

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

//fomction pour fermer la fenetre//

int		ft_close(int keycode, t_data *img)
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

//fait un carre avec la size//

void	drawPlayer2d(t_data *data, int size)
{
	int x2 =  -size;
	int y2 =  -size;
	
	while (y2 <= size)
	{
		while (x2 <= size)
		{
			my_mlx_pixel_put(&data->background, data->x + x2, data->y + y2, 0XFFFF00);
			x2++;
		}
		x2 =  -size;
		y2++;
	}
}

//##############################################################################

//touche avance recul et pivote//

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

//dessine le rayon du player//

void	drawlineplayer(t_data *data)
{
	int x1 = data->x;
	int y1 = data->y;
	int x2 = x1 + data->dx * 5;
	int y2 = y1 + data->dy * 5;
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx < 0)
	{
		x1 = x2;
		y1 = y2;
		x2 = data->x;
		y2 = data->y;
	}
	int x = x1;
	int y = 0;
	while (x < x2)
	{
		y = y1 + dy * (x - x1) / dx;
		my_mlx_pixel_put(&data->background, x , y, 0xFFFF00);
		x++;
	}
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

//###############################################################################

//dessine les lisgne vertical//

void	drawverticalline(t_data *data, int x, int y, int y2, int color)
{
	while (y < y2)
	{
		my_mlx_pixel_put(&data->background, x , y, color);
		y++;
	}
}

//###############################################################################

float	dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

//###############################################################################

//peint le ciel et floor ful screen//

void	full_screen_grey(t_img *img)
{
	int x = 0;
	int y = 0;
	
	while (y < screenHeight / 2)
	{
		while (x < screenWidth)
		{
			my_mlx_pixel_put(img, x, y, 0x99CCFF);
			x++;
		}
		x = 0;
		y++;
	}
	while (y < screenHeight)
	{
		while (x < screenWidth)
		{
			my_mlx_pixel_put(img, x, y, 0x606060);
			x++;
		}
		x = 0;
		y++;
	}
}

//###############################################################################

//dessine un carre//

void	put_quad_map(t_img *img, int x, int y, int max)
{
	while (x < max)
	{
		my_mlx_pixel_put(img, x, y, img->colormap1);
		y++;
	}
}

//###############################################################################

//dessine la map besoin de maps=size de la minimap et mapX mapY taille de la map//

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

//fonction qui loop avc loophook//

// int		render_next_frame(t_data *data)
// {
// 	if (data->refresh)
// 	{
// 		//full_screen_grey(&data->background);
// 		//drawRays3D(data);
// 		//drawlineplayer(data);
// 		//raycaster(data);
// 		//drawMap(&data->background);
// 		//drawPlayer2d(data, 4);
// 		//mlx_put_image_to_window(data->mlx, data->win, data->background.img, 0, 0);
// 	}
// 	data->refresh = 0;
// 	return (0);
// }

//##############################################################################

//initialise mes donné//

// void	ft_init(t_data *img)
// {
// 	if (img->refresh == 0)
// 	{
// 		//img->dx = -1, img->dy = 0;
// 		//img->x = 22, img->y = 12;
// 		//img->color = create_trgb(0, 255, 255, 0);
// 		//img->planeX = 0, img->planeY = 0.66;
// 	}
// 	//drawPlayer(img);
// }

// //##############################################################################

// void		ft_ray(void)
// {
// 	t_data data;
// 	memset(&data, 0, sizeof(t_data));
// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, screenWidth, screenHeight, "***Cub3D***");
// 	data.background.img = mlx_new_image(data.mlx, screenWidth, screenHeight);
// 	data.background.addr = mlx_get_data_addr(data.background.img, &data.background.bits_per_pixel, &data.background.line_length, &data.background.endian);
// 	mlx_put_image_to_window(data.mlx, data.win, data.background.img, 0, 0);
// 	ft_init(&data);
// 	data.refresh = 1;
// 	printf("datax = %f\n", data.x);
// 	mlx_hook(data.win, 2, 1L<<0, key_hook2, &data);
// 	mlx_loop_hook(data.mlx, render_next_frame, &data);
// 	mlx_loop(data.mlx);
// }