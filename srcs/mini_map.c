/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:36:19 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/27 15:20:23 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	put_quad_map(t_data *data, int x, int y, int max)
{
    while (y < max)
    {
		    my_mlx_pixel_put(&data->background, x, y, data->colormap1);
            y++;
    }
}


void	drawPlayer2d(t_data *data, int size)
{
    //int mapS = 10;
	int x2 =  -size;
	int y2 =  -size;
	
	while (y2 <= size)
	{
		while (x2 <= size)
		{
			my_mlx_pixel_put(&data->background, (data->y * data->mapS) + x2, (data->x * data->mapS) + y2, 0XFFFF00);
			x2++;
		}
		x2 =  -size;
		y2++;
	}
}

void	drawMap(t_data *data)
{
	int x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;
	int xa = 0;

	data->colormap1 = 0x000000;

	while (data->par.map[y])
	{
		while (data->par.map[y][x])
		{
			if (data->par.map[y][x] == '1')
				data->colormap1 = 0xFFFFFF;
			else
				data->colormap1 = 0x000000;
			xo = x * data->mapS;
			yo = y * data->mapS;
			xa = 0 + xo + 1;
			while (xa <  data->mapS + xo - 1)
			{
				put_quad_map(data, xa, 0 + yo + 1, data->mapS + yo - 1);
				xa++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
