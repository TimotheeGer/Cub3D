/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:41:22 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 19:06:22 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	init_raycast_part_two(t_data *d)
{
	d->r.lineh = (int)(d->r.h / d->r.pwlldst);
	d->r.drws = -d->r.lineh / 2 + d->r.h / 2;
	if (d->r.drws < 0)
		d->r.drws = 0;
	d->r.drwe = d->r.lineh / 2 + d->r.h / 2;
	if (d->r.drwe >= d->r.h)
		d->r.drwe = d->r.h - 1;
	d->r.step = 1.0 * 512 / d->r.lineh;
	d->r.texpos = (d->r.drws - d->r.h / 2 + d->r.lineh / 2) * d->r.step;
	if (d->r.side == 0)
		d->r.wallx = d->y + d->r.pwlldst * d->r.rdiry;
	else
		d->r.wallx = d->x + d->r.pwlldst * d->r.rdirx;
	d->r.wallx -= floor((d->r.wallx));
	d->r.texx = (int)(d->r.wallx * (double)512);
	if (d->r.side == 0 && d->r.rdirx > 0)
		d->r.texx = 512 - d->r.texx - 1;
	if (d->r.side == 1 && d->r.rdiry < 0)
		d->r.texx = 512 - d->r.texx - 1;
}

void	init_raycast_part_three(t_data *d)
{
	d->r.texy = (int)d->r.texpos & (512 - 1);
	d->r.texpos += d->r.step;
	d->r.i = d->r.texy * 2048 + d->r.texx * 4;
	d->r.color = 0;
}

void	raycast_part_four(t_data *d)
{
	if (d->r.side == 0 && d->r.rdirx < 0)
	{
		d->r.color = create_trgb(0,
				(int)(unsigned char)d->par.t_no.addr[d->r.i + 2],
				(int)(unsigned char)d->par.t_no.addr[d->r.i + 1],
				(int)(unsigned char)d->par.t_no.addr[d->r.i]);
	}
	if (d->r.side == 0 && d->r.rdirx > 0)
	{
		d->r.color = create_trgb(0,
				(int)(unsigned char)d->par.t_so.addr[d->r.i + 2],
				(int)(unsigned char)d->par.t_so.addr[d->r.i + 1],
				(int)(unsigned char)d->par.t_so.addr[d->r.i]);
	}
}

void	raycast_part_five(t_data *d)
{
	if (d->r.side == 1 && d->r.rdiry > 0)
	{
		d->r.color = create_trgb(0,
				(int)(unsigned char)d->par.t_ea.addr[d->r.i + 2],
				(int)(unsigned char)d->par.t_ea.addr[d->r.i + 1],
				(int)(unsigned char)d->par.t_ea.addr[d->r.i]);
	}
	if (d->r.side == 1 && d->r.rdiry < 0)
	{
		d->r.color = create_trgb(0,
				(int)(unsigned char)d->par.t_we.addr[d->r.i + 2],
				(int)(unsigned char)d->par.t_we.addr[d->r.i + 1],
				(int)(unsigned char)d->par.t_we.addr[d->r.i]);
	}
}

void	raycaster(t_data *d)
{
	d->r.x = 0;
	d->r.w = d->par.rx;
	d->r.h = d->par.ry;
	while (d->r.x < d->r.w)
	{
		init_raycast_part_one(d);
		raycast_part_two(d);
		raycast_part_three(d);
		init_raycast_part_two(d);
		d->r.y = d->r.drws;
		while (d->r.y <= d->r.drwe)
		{
			init_raycast_part_three(d);
			if (d->r.y < d->r.h && d->r.x < d->r.w)
			{
				raycast_part_four(d);
				raycast_part_five(d);
				my_mlx_pixel_put(&d->screen, d->r.x, d->r.y, d->r.color);
			}
			d->r.y++;
		}
		d->r.x++;
	}
}
