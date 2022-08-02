/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:55:20 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:38:39 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	init_floor_one(t_data *d)
{
	d->f.x = 0;
	d->f.rdx0 = d->dx - d->planex;
	d->f.rdy0 = d->dy - d->planey;
	d->f.rdx1 = d->dx + d->planex;
	d->f.rdy1 = d->dy + d->planey;
	d->f.p = d->f.y - d->par.ry / 2;
	d->f.posz = 0.5 * d->par.ry;
	d->f.rwdist = d->f.posz / d->f.p;
	d->f.flrstpx = d->f.rwdist * (d->f.rdx1 - d->f.rdx0) / d->par.rx;
	d->f.flrstpy = d->f.rwdist * (d->f.rdy1 - d->f.rdy0) / d->par.rx;
	d->f.flrx = d->x + d->f.rwdist * d->f.rdx0;
	d->f.flry = d->y + d->f.rwdist * d->f.rdy0;
}

void	ft_floor(t_data *d)
{
	d->f.y = d->f.h / 2 + 1;
	while (d->f.y < d->par.ry)
	{
		d->f.y++;
		init_floor_one(d);
		while (d->f.x < d->par.rx)
		{
			d->f.x++;
			d->f.cellx = (int)(d->f.flrx);
			d->f.celly = (int)(d->f.flry);
			d->f.tx = (int)(d->par.t_f.width
					*(d->f.flrx - d->f.cellx)) & (d->par.t_f.width - 1);
			d->f.ty = (int)(d->par.t_f.heigth
					* (d->f.flry - d->f.celly)) & (d->par.t_f.heigth - 1);
			d->f.flrx += d->f.flrstpx;
			d->f.flry += d->f.flrstpy;
			d->f.i = d->f.ty * d->par.t_f.line_len + d->f.tx * 4;
			d->f.color = create_trgb(0,
					(int)(unsigned char)d->par.t_f.addr[d->f.i + 2],
					(int)(unsigned char)d->par.t_f.addr[d->f.i + 1],
					(int)(unsigned char)d->par.t_f.addr[d->f.i]);
			my_mlx_pixel_put(&d->screen, d->f.x, d->f.y, d->f.color);
		}
	}
}
