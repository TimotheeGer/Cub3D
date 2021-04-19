/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/19 16:31:47 by tigerber         ###   ########.fr       */
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

int     main(void)
{
	void	*mlx;
	t_data	img;

	mlx = NULL;
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	return (0);
}
