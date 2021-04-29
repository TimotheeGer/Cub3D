/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/29 15:46:59 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1024
#define screenHeight 512

int		worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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

typedef struct	s_data
{
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	i;
	int		j;
	int		y;
	int		x;
	int		color;
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//###############################################################################

int		key_hook(int keycode, t_data *img)
{
	if (keycode == 'a')
		img->x-=5;
	if (keycode == 'd')
		img->x+=5;
	if (keycode == 'w')
		img->y-=5;
	if (keycode == 's')
		img->y+=5;
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
	//mlx_mouse_hook(img.win, mouse_hook, &img);
	//printf("button = %d\n", button);
	// if (x)
	// 	printf("enter\n");
	// if (!x)
	// 	printf("out\n");
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

void	size_pixel(t_data *img, int x, int y, int size)
{
	int xx = x;
	int yy = y;
	
	while (yy < y + size)
	{
		while (xx < x + size)
		{
			my_mlx_pixel_put(img, xx, yy, 0x00FF00);
			xx++;
		}
		xx = x;
		yy++;
	}

}

// void	clearaddr(t_data *img)
// {
// 	int i = 0;
// 	while (img->addr[i] != '\0')
// 	{
// 		img->addr = 0;
// 		i++;
// 	}
// }

int		render_next_frame(t_data *img)
{
	img->img = mlx_new_image(img->mlx, screenWidth, screenHeight);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	size_pixel(img, img->x, img->y, 8);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

//##############################################################################

void	init(t_data *img)
{
	img->x = 300;
	img->y = 300;
	img->color = create_trgb(0, 255, 255, 0);
}

int		main(void)
{
	t_data img;
	
	img.mlx = mlx_init();
 	img.win = mlx_new_window(img.mlx, screenWidth, screenHeight, "***Cub3D***");
	img.img = mlx_new_image(img.mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	init(&img);
	mlx_hook(img.win, 3, 1L<<0, key_hook, &img);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
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
