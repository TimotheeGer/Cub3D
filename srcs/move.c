/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:10:05 by tigerber          #+#    #+#             */
/*   Updated: 2021/07/06 13:44:43 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void  rotation(int keycode, t_data *d)
{
  	if (keycode == 65361)
	{
      		double oldDirX = d->dx;
      		d->dx = d->dx * cos(d->rota) - d->dy * sin(d->rota);
      		d->dy = oldDirX * sin(d->rota) + d->dy * cos(d->rota);
      		double oldPlaneX = d->planeX;
      		d->planeX = d->planeX * cos(d->rota) - d->planeY * sin(d->rota);
      		d->planeY = oldPlaneX * sin(d->rota) + d->planeY * cos(d->rota);
	}
	if (keycode == 65363)
	{
			double oldDirX = d->dx;
      		d->dx = d->dx * cos(-d->rota) - d->dy * sin(-d->rota);
      		d->dy = oldDirX * sin(-d->rota) + d->dy * cos(-d->rota);
      		double oldPlaneX = d->planeX;
      		d->planeX = d->planeX * cos(-d->rota) - d->planeY * sin(-d->rota);
      		d->planeY = oldPlaneX * sin(-d->rota) + d->planeY * cos(-d->rota);
	}
}

void  move_lateral(int keycode, t_data *d)
{
    if (keycode == 'd')
	{
		if(d->par.map[(int)(d->x + d->planeX * d->move)][(int)(d->y)] == '0')
            d->x += d->planeX * d->move;
        if(d->par.map[(int)(d->x)][(int)(d->y + d->planeY * d->move)] == '0')
            d->y += d->planeY * d->move;
	}
    if (keycode == 'a')
	{
		if(d->par.map[(int)(d->x - d->planeX * d->move)][(int)(d->y)] == '0')
            d->x -= d->planeX * d->move;
        if(d->par.map[(int)(d->x)][(int)(d->y - d->planeY * d->move)] == '0')
            d->y -= d->planeY * d->move;
	}
}

void  move_front_back(int keycode, t_data *d)
{
  if (keycode == 'w')
	{
	    if(d->par.map[(int)(d->x + d->dx * d->move)][(int)(d->y)] == '0')
            d->x += d->dx * d->move;
        if(d->par.map[(int)d->x][(int)(d->y + d->dy * d->move)] == '0')
            d->y += d->dy * d->move;
	}
	if (keycode == 's')
	{
	    if(d->par.map[(int)(d->x - d->dx * d->move)][(int)(d->y)] == '0')
            d->x -= d->dx * d->move;
        if(d->par.map[(int)(d->x)][(int)(d->y - d->dy * d->move)] == '0')
            d->y -= d->dy * d->move;
	}
}

int		key_hook(int keycode, t_data *d)
{
	ft_escape(keycode, d);
    move_front_back(keycode, d);
    move_lateral(keycode, d);
    rotation(keycode, d);
	return (0);
}