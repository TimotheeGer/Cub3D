/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:10:05 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:14:31 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	rotation(int keycode, t_data *d)
{
	if (keycode == 65361)
	{
		d->olddirx = d->dx;
		d->dx = d->dx * cos(d->rota) - d->dy * sin(d->rota);
		d->dy = d->olddirx * sin(d->rota) + d->dy * cos(d->rota);
		d->oldplanex = d->planex;
		d->planex = d->planex * cos(d->rota) - d->planey * sin(d->rota);
		d->planey = d->oldplanex * sin(d->rota) + d->planey * cos(d->rota);
	}
	if (keycode == 65363)
	{
		d->olddirx = d->dx;
		d->dx = d->dx * cos(-d->rota) - d->dy * sin(-d->rota);
		d->dy = d->olddirx * sin(-d->rota) + d->dy * cos(-d->rota);
		d->oldplanex = d->planex;
		d->planex = d->planex * cos(-d->rota) - d->planey * sin(-d->rota);
		d->planey = d->oldplanex * sin(-d->rota) + d->planey * cos(-d->rota);
	}
}

void	move_lateral(int keycode, t_data *d)
{
	if (keycode == 'd')
	{
		if (d->par.map[(int)(d->x + d->planex * (d->move * 2))]
			[(int)(d->y)] == '0')
			d->x += d->planex * d->move;
		if (d->par.map[(int)(d->x)]
			[(int)(d->y + d->planey * (d->move * 2))] == '0')
			d->y += d->planey * d->move;
	}
	if (keycode == 'a')
	{
		if (d->par.map[(int)(d->x - d->planex * (d->move * 2))]
			[(int)(d->y)] == '0')
			d->x -= d->planex * d->move;
		if (d->par.map[(int)(d->x)]
			[(int)(d->y - d->planey * (d->move * 2))] == '0')
			d->y -= d->planey * d->move;
	}
}

void	move_front_back(int keycode, t_data *d)
{
	if (keycode == 'w')
	{
		if (d->par.map[(int)floor(d->x + d->dx * (d->move * 2))]
			[(int)(d->y)] == '0')
			d->x += d->dx * d->move;
		if (d->par.map[(int)floor(d->x)]
			[(int)floor(d->y + d->dy * (d->move * 2))] == '0')
			d->y += d->dy * d->move;
	}
	if (keycode == 's')
	{
		if (d->par.map[(int)floor(d->x - d->dx * (d->move * 2))]
			[(int)(d->y)] == '0')
			d->x -= d->dx * d->move;
		if (d->par.map[(int)floor(d->x)]
			[(int)floor(d->y - d->dy * (d->move * 2))] == '0')
			d->y -= d->dy * d->move;
	}
}

int	key_hook(int keycode, t_data *d)
{
	ft_escape(keycode, d, 0);
	move_front_back(keycode, d);
	move_lateral(keycode, d);
	rotation(keycode, d);
	return (0);
}
