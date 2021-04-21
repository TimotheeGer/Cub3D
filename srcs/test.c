/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/21 16:47:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

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

typedef struct	s_data
{
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	i;
	int		j;
	int		color;
	void	*mlx;
	void	*win;
	
}				t_data;

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
	//mlx_key_hook(img.win, key_hook, &img);
	(void)img;
	printf("%d\n", keycode);
	if (keycode == 113)
		printf("hello hook!\n");
	return (0);
}


int		mouse_hook(int button, int x, int y, t_data *img)
{
	//mlx_mouse_hook(img.win, mouse_hook, &img);
	
	if (x || y)
	{
		printf("button = %d\n", button);
		printf("x y = %d,%d\n", x, y);
	}
	(void)img;
	return (0);
}
#include <stdlib.h>
int		close(int keycode, t_data *img)
{
	(void)img;
	(void)keycode;
	//if (keycode == 65307)
	//{
		mlx_destroy_window(img->mlx, img->win);
		free(img->img);
		free(img->addr);
		free(img->mlx);
		free(img->win);
		exit(0);
	//}
	return (0);

}

#include <string.h>
int     main(void)
{
	t_data	img;
	img.color = 0;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 1920, 1080, "hello world!");
	img.img = mlx_new_image(img.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	 							&img.line_length, &img.endian);
	
	//mlx_key_hook(img.win, key_hook, &img);
	// mlx_mouse_hook(img.win, mouse_hook, &img);
	mlx_hook(img.win, 33, 0, close, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
	return (0);
}
