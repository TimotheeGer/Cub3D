/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:07:52 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:14:31 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	init_raycast_part_one(t_data *d)
{
	d->r.camx = 2.0 * d->r.x / (double)d->r.w - 1.0;
	d->r.rdirx = d->dx + d->planex * d->r.camx;
	d->r.rdiry = d->dy + d->planey * d->r.camx;
	d->r.mapx = (int)d->x;
	d->r.mapy = (int)d->y;
	d->r.sdstx = 0;
	d->r.sdsty = 0;
	d->r.dltdx = fabs(1 / d->r.rdirx);
	d->r.dltdy = fabs(1 / d->r.rdiry);
	d->r.pwlldst = 0;
	d->r.stpx = 0;
	d->r.stpy = 0;
	d->r.hit = 0;
	d->r.side = 0;
}

void	raycast_part_two(t_data *d)
{
	if (d->r.rdirx < 0)
	{
		d->r.stpx = -1;
		d->r.sdstx = (d->x - d->r.mapx) * d->r.dltdx;
	}
	else
	{
		d->r.stpx = 1;
		d->r.sdstx = (d->r.mapx + 1.0 - d->x) * d->r.dltdx;
	}
	if (d->r.rdiry < 0)
	{
		d->r.stpy = -1;
		d->r.sdsty = (d->y - d->r.mapy) * d->r.dltdy;
	}
	else
	{
		d->r.stpy = 1;
		d->r.sdsty = (d->r.mapy + 1.0 - d->y) * d->r.dltdy;
	}
}

double	ft_paperwalldist(int i, t_data *d)
{
	if (i == 1)
		return ((d->r.mapx - d->x + (1 - d->r.stpx) / 2) / d->r.rdirx);
	if (i == 2)
		return ((d->r.mapy - d->y + (1 - d->r.stpy) / 2) / d->r.rdiry);
	return (0);
}

void	raycast_part_three(t_data *d)
{
	while (d->r.hit == 0)
	{
		if (d->r.sdstx < d->r.sdsty)
		{
			d->r.sdstx += d->r.dltdx;
			d->r.mapx += d->r.stpx;
			d->r.side = 0;
		}
		else
		{
			d->r.sdsty += d->r.dltdy;
			d->r.mapy += d->r.stpy;
			d->r.side = 1;
		}
		if (d->par.map[d->r.mapx][d->r.mapy] == '1')
			d->r.hit = 1;
	}
	if (d->r.side == 0)
		d->r.pwlldst = ft_paperwalldist(1, d);
	else
		d->r.pwlldst = ft_paperwalldist(2, d);
}
