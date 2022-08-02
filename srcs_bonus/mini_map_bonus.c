/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:36:19 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:15:42 by tigerber         ###   ########.fr       */
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

void	draw_player(t_data *data, int size)
{
	int	x;
	int	y;

	x = -size;
	y = -size;
	while (y <= size)
	{
		while (x <= size)
		{
			my_mlx_pixel_put(&data->screen, (data->y * data->maps) + x,
				(data->x * data->maps) + y, 0XFFFF00);
			x++;
		}
		x = -size;
		y++;
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

void	draw_map(t_data *d)
{
	init_map(d);
	while (d->par.map[d->m.y])
	{
		while (d->par.map[d->m.y][d->m.x])
		{
			if (d->par.map[d->m.y][d->m.x] == '1')
				d->colormap1 = 0xFFFFFF;
			else if (d->par.map[d->m.y][d->m.x] == '0')
				d->colormap1 = 0x000000;
			d->m.xo = d->m.x * d->maps;
			d->m.yo = d->m.y * d->maps;
			d->m.xa = 0 + d->m.xo + 1;
			while (d->m.xa < d->maps + d->m.xo - 1)
			{
				if (d->par.map[d->m.y][d->m.x] == '1'
					|| d->par.map[d->m.y][d->m.x] == '0')
					pmap(d, d->m.xa, 0 + d->m.yo + 1, d->maps + d->m.yo - 1);
				d->m.xa++;
			}
			d->m.x++;
		}
		d->m.x = 0;
		d->m.y++;
	}
}
