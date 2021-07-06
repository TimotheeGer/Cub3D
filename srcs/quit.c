/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:43:57 by tigerber          #+#    #+#             */
/*   Updated: 2021/07/06 13:48:00 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void	ft_destroy(t_data *d)
{
	if (d->par.t_no.img)
		mlx_destroy_image(d->mlx, d->par.t_no.img);
	if (d->par.t_so.img)
		mlx_destroy_image(d->mlx, d->par.t_so.img);
	if (d->par.t_we.img)	
		mlx_destroy_image(d->mlx, d->par.t_we.img);
	if (d->par.t_ea.img)
		mlx_destroy_image(d->mlx, d->par.t_ea.img);
	if (d->par.t_f.img)
		mlx_destroy_image(d->mlx, d->par.t_f.img);
	if (d->par.t_sp.img)
		mlx_destroy_image(d->mlx, d->par.t_sp.img);
	if (d->screen.img)
		mlx_destroy_image(d->mlx, d->screen.img);
	if (d->win)
	 	mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
}

int	ft_escape(int keycode, t_data *d)
{
	if (keycode == 65307)
	{
		ft_destroy(d);
		free_struct(&d->par);
		ft_lstclear_sp(d->par.sp_begin);
		printf("error structur\n");
		exit(0);
	}
	return (0);
}

int	ft_cross(t_data *d)
{
	ft_destroy(d);
	free_struct(&d->par);
	ft_lstclear_sp(d->par.sp_begin);
	exit(0);
}
