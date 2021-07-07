/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:36:19 by tigerber          #+#    #+#             */
/*   Updated: 2021/07/07 15:18:52 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	pmap(t_data *data, int x, int y, int max)
{
	while (y < max)
	{
		my_mlx_pixel_put(&data->screen, x, y, data->colormap1);
		y++;
	}
}

void	drawPlayer2d(t_data *data, int size)
{
	int	x2;
	int	y2;

	x2 = -size;
	y2 = -size;
	while (y2 <= size)
	{
		while (x2 <= size)
		{
			my_mlx_pixel_put(&data->screen, (data->y * data->mapS) + x2,
				(data->x * data->mapS) + y2, 0XFFFF00);
			x2++;
		}
		x2 = -size;
		y2++;
	}
}

void	init_map(t_data *d)
{
	d->m.x = 0;
	d->m.y = 0;
	d->m.xo = 0;
	d->m.xa = 0;
	d->colormap1 = 0x0000FF;
}

void	drawMap(t_data *d)
{
	init_map(d);
	while (d->par.map[d->m.y])
	{
		while (d->par.map[d->m.y][d->m.x])
		{
			if (d->par.map[d->m.y][d->m.x] == '1')
				d->colormap1 = 0xFFFFFF;
			else
				d->colormap1 = 0x000000;
			d->m.xo = d->m.x * d->mapS;
			d->m.yo = d->m.y * d->mapS;
			d->m.xa = 0 + d->m.xo + 1;
			while (d->m.xa < d->mapS + d->m.xo - 1)
			{
				pmap(d, d->m.xa, 0 + d->m.yo + 1, d->mapS + d->m.yo - 1);
				d->m.xa++;
			}
			d->m.x++;
		}
		d->m.x = 0;
		d->m.y++;
	}
}
