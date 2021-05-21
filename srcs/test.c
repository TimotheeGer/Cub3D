/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/21 18:05:53 by tigerber         ###   ########.fr       */
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
// 	    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
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

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//##############################################################################

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//###############################################################################

//peint le ciel et floor ful screen//

void	full_screen_grey(t_data *data)
{
	int x = 0;
	int y = 0;
	int color = data->colorC;
	int color2 = data->colorF;
	while (y < data->par.Ry / 2)
	{
		while (x < data->par.Rx)
		{
			my_mlx_pixel_put(&data->background, x, y, color);
			x++;
		}
		if (y % 4 == 0)
			color++;
		x = 0;
		y++;
	}
	while (y < data->par.Ry)
	{
		while (x < data->par.Rx)
		{
			my_mlx_pixel_put(&data->background, x, y, color2);
			x++;
		}
		x = 0;
		y++;
	}
}

//###############################################################################

void	ft_vue(t_data *data)
{
	if (data->perso.vue == 'N')
		data->dx = -1;
	if (data->perso.vue == 'N')
		data->planeY = 0.66;	
	if (data->perso.vue == 'S')
		data->dx = 1;
	if (data->perso.vue == 'S')
		data->planeY = -0.66;
	if (data->perso.vue == 'W')
		data->dy = -1;
	if (data->perso.vue == 'W')
		data->planeX = -0.66;
	if (data->perso.vue == 'E')
		data->dy = 1;
	if (data->perso.vue == 'E')
		data->planeX= 0.66;		
}

//###############################################################################

void	ft_init(t_data *data)
{
		printf("data posx = %d\n", data->perso.pos_x);
		// ft_vue(data);
		data->dx = -1, data->dy = 0;
		data->x = data->perso.pos_x + 0.5, data->y = data->perso.pos_y + 0.5;
		data->colorF = create_trgb(0, data->par.F[0], data->par.F[1], data->par.F[2]);
		data->colorC = create_trgb(0, data->par.C[0], data->par.C[1], data->par.C[2]);
		data->planeX = 0, data->planeY = 0.66;
}

//###############################################################################

int		render_next_frame(t_data *data)
{
	if (data->refresh)
	{
		full_screen_grey(data);
		raycaster(data);
		mlx_put_image_to_window(data->mlx, data->win, data->background.img, 0, 0);
	}
	data->refresh = 0;
	return (0);
}

//###############################################################################

void		ft_ray(t_data *data)
{
	printf("rx = %d\n", data->par.Rx);
	printf("data = \n");
	data->mlx = mlx_init();
	data->background.img = mlx_new_image(data->mlx, data->par.Rx, data->par.Ry);
	data->background.addr = mlx_get_data_addr(data->background.img, &data->background.bits_per_pixel, &data->background.line_length, &data->background.endian);
	data->win = mlx_new_window(data->mlx, data->par.Rx, data->par.Ry, "***Cub3D***");
	ft_init(data);
	data->refresh = 1;
	printf("dat->x = %f\n", data->x);
	mlx_hook(data->win, 2, 1L<<0, key_hook2, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}
