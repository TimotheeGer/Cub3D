/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/11 12:57:41 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/cub3D.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1080
#define screenHeight 920
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

//##############################################################################

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//##############################################################################

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//###############################################################################

//peint le ciel et floor ful screen//

void	full_screen_bicolor(t_data *data)
{
	int x = 0;
	int y = 0;
	int color = data->colorC;
	while (y < data->par.Ry / 2)
	{
		while (x < data->par.Rx)
		{
			my_mlx_pixel_put(&data->screen, x, y, color);
			x++;
		}
		if (y % 4 == 0)
			color++;
		x = 0;
		y++;
	}
	while (y < data->par.Ry)
	{
		while (x < data->par.Rx)
		{
			my_mlx_pixel_put(&data->screen, x, y, data->colorF);
			x++;
		}
		x = 0;
		y++;
	}
}

//###############################################################################

void	ft_vue(t_data *data)
{
	if (data->perso.vue == 'N')
		data->dx = -1;
	if (data->perso.vue == 'N')
		data->planeY = 0.66;	
	if (data->perso.vue == 'S')
		data->dx = 1;
	if (data->perso.vue == 'S')
		data->planeY = -0.66;
	if (data->perso.vue == 'W')
		data->dy = -1;
	if (data->perso.vue == 'W')
		data->planeX = -0.66;
	if (data->perso.vue == 'E')
		data->dy = 1;
	if (data->perso.vue == 'E')
		data->planeX= 0.66;		
}

//###############################################################################

void	ft_init(t_data *d)
{
		ft_vue(d);
		d->f.w = d->par.Rx;
		d->f.h = d->par.Ry;
		d->mapS = 3;
		d->x = d->perso.pos_x + 0.5, d->y = d->perso.pos_y + 0.5;
		d->colorF = create_trgb(0, d->par.F[0], d->par.F[1], d->par.F[2]);
		d->colorC = create_trgb(0, d->par.C[0], d->par.C[1], d->par.C[2]);
		d->rota = 0.08;
		d->move = 0.5;
}

//###############################################################################

int		render_next_frame(t_data *data)
{
	if (data->refresh)
	{
		full_screen_bicolor(data);
		raycaster(data);
		drawMap(data);
		drawPlayer2d(data, 1 / 2);
		mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
	}
	data->refresh = 0;
	return (0);
}

//###############################################################################

void			ft_get_text(t_data *d)
{
	d->par.t_no.img = mlx_xpm_file_to_image(d->mlx, d->par.t_no.path,
								&d->par.t_no.width, &d->par.t_no.heigth);
    d->par.t_no.addr = mlx_get_data_addr(d->par.t_no.img, &d->par.t_no.b_p_pix,
								&d->par.t_no.line_len, &d->par.t_no.endian);							
	d->par.t_so.img = mlx_xpm_file_to_image(d->mlx, d->par.t_so.path, 
								&d->par.t_so.width, &d->par.t_so.heigth);
    d->par.t_so.addr = mlx_get_data_addr(d->par.t_so.img, &d->par.t_so.b_p_pix,
								&d->par.t_so.line_len, &d->par.t_so.endian);
	d->par.t_we.img = mlx_xpm_file_to_image(d->mlx, d->par.t_we.path, 
								&d->par.t_we.width, &d->par.t_we.heigth);
    d->par.t_we.addr = mlx_get_data_addr(d->par.t_we.img, &d->par.t_we.b_p_pix,
								&d->par.t_we.line_len,&d->par.t_we.endian);
	d->par.t_ea.img = mlx_xpm_file_to_image(d->mlx, d->par.t_ea.path, 
								&d->par.t_ea.width, &d->par.t_ea.heigth);
    d->par.t_ea.addr = mlx_get_data_addr(d->par.t_ea.img, &d->par.t_ea.b_p_pix,
								&d->par.t_ea.line_len, &d->par.t_ea.endian);
	d->par.t_sol.img = mlx_xpm_file_to_image(d->mlx, "./srcs/sol2.xpm", 
								&d->par.t_sol.width, &d->par.t_sol.heigth);
    d->par.t_sol.addr = mlx_get_data_addr(d->par.t_sol.img, &d->par.t_sol.b_p_pix,
								&d->par.t_sol.line_len, &d->par.t_sol.endian);
	d->par.t_sp.img = mlx_xpm_file_to_image(d->mlx, d->par.t_sp.path, 
								&d->par.t_sp.width, &d->par.t_sp.heigth);
    d->par.t_sp.addr = mlx_get_data_addr(d->par.t_sp.img, &d->par.t_sp.b_p_pix,
								&d->par.t_sp.line_len, &d->par.t_sp.endian);		
}

//###############################################################################

void		ft_ray(t_data *data)
{
	data->mlx = mlx_init();
	data->screen.img = mlx_new_image(data->mlx, data->par.Rx, data->par.Ry);
	data->screen.addr = mlx_get_data_addr(data->screen.img, 
							&data->screen.bits_per_pixel,
							&data->screen.line_length,
							&data->screen.endian);
	data->win = mlx_new_window(data->mlx, data->par.Rx, data->par.Ry, "***Cub3D***");
	ft_init(data);
	ft_get_text(data);
	data->refresh = 1;
	mlx_hook(data->win, 2, 1L<<0, key_hook2, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}
