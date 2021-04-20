/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/20 16:40:19 by tigerber         ###   ########.fr       */
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
	
}				t_data;

typedef struct  s_vars 
{
	
    void        *mlx;
    void        *win;
	
}               t_vars;

int             key_hook(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	(void)vars;
	if (keycode == 113)
		printf("Hello from key_hook!\n");
	return (0);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int     main(void)
{
	t_vars vars;
	// int		color;
	// void	*mlx_win;
	// void	*mlx;
	// t_data	img;
	// int i = 0;
	// int j = 0;
	// color = create_trgb(0, 116, 208, 241);
	// //mlx = NULL;
	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "hello world!");
	// img.img = mlx_new_image(mlx, 1920, 1080);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	//  							&img.line_length, &img.endian);
	
	// while (i < 1920)
	// {							 
	// 	while (j < 540)
	// 	{
	// 		my_mlx_pixel_put(&img, i, j, color);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	i++;
	// }
	// i = 0;
	// j = 540;
	// color = create_trgb(0, 20, 148, 20);
	// while (i < 1920)
	// {							 
	// 	while (j < 1080)
	// 	{
	// 		my_mlx_pixel_put(&img, i, j, color);
	// 		j++;
	// 	}
	// 	j = 540;
	// 	i++;
	// }
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(mlx);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
