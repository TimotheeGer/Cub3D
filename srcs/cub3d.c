/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 19:06:08 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/cub3D.h"

void	ft_init(t_data *d)
{
	ft_vue(d);
	d->refresh = 1;
	d->f.w = 1400;
	d->f.h = 720;
	d->par.rx = 1400;
	d->par.ry = 720;
	d->maps = 5;
	d->x = d->perso.pos_x + 0.5;
	d->y = d->perso.pos_y + 0.5;
	d->colorf = create_trgb(0, d->par.fl[0], d->par.fl[1], d->par.fl[2]);
	d->colorc = create_trgb(0, d->par.ci[0], d->par.ci[1], d->par.ci[2]);
	d->rota = 0.08;
	d->move = 0.5;
}

int	render_next_frame(t_data *data)
{
	if (data->screen.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->screen.img);
	}
	data->screen.img = mlx_new_image(data->mlx, data->par.rx, data->par.ry);
	data->screen.addr = mlx_get_data_addr(data->screen.img,
			&data->screen.bits_per_pixel,
			&data->screen.line_length,
			&data->screen.endian);
	full_screen_bicolor(data);
	raycaster(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
	return (0);
}

void	ft_get_addr(t_data *d)
{
	d->par.t_no.addr = mlx_get_data_addr(d->par.t_no.img, &d->par.t_no.b_p_pix,
			&d->par.t_no.line_len, &d->par.t_no.endian);
	d->par.t_so.addr = mlx_get_data_addr(d->par.t_so.img, &d->par.t_so.b_p_pix,
			&d->par.t_so.line_len, &d->par.t_so.endian);
	d->par.t_we.addr = mlx_get_data_addr(d->par.t_we.img, &d->par.t_we.b_p_pix,
			&d->par.t_we.line_len, &d->par.t_we.endian);
	d->par.t_ea.addr = mlx_get_data_addr(d->par.t_ea.img, &d->par.t_ea.b_p_pix,
			&d->par.t_ea.line_len, &d->par.t_ea.endian);
	d->par.t_f.addr = mlx_get_data_addr(d->par.t_f.img, &d->par.t_f.b_p_pix,
			&d->par.t_f.line_len, &d->par.t_f.endian);
}

void	ft_get_text(t_data *d)
{	
	d->par.t_no.img = mlx_xpm_file_to_image(d->mlx, d->par.t_no.path,
			&d->par.t_no.width, &d->par.t_no.heigth);
	if (!(d->par.t_no.img))
		ft_escape(65307, d, 1);
	d->par.t_so.img = mlx_xpm_file_to_image(d->mlx, d->par.t_so.path,
			&d->par.t_so.width, &d->par.t_so.heigth);
	if (!(d->par.t_so.img))
		ft_escape(65307, d, 1);
	d->par.t_we.img = mlx_xpm_file_to_image(d->mlx, d->par.t_we.path,
			&d->par.t_we.width, &d->par.t_we.heigth);
	if (!(d->par.t_we.img))
		ft_escape(65307, d, 1);
	d->par.t_ea.img = mlx_xpm_file_to_image(d->mlx, d->par.t_ea.path,
			&d->par.t_ea.width, &d->par.t_ea.heigth);
	if (!(d->par.t_ea.img))
		ft_escape(65307, d, 1);
	d->par.t_f.img = mlx_xpm_file_to_image(d->mlx, "./srcs/texture/sol2.xpm",
			&d->par.t_f.width, &d->par.t_f.heigth);
	if (!(d->par.t_f.img))
		ft_escape(65307, d, 1);
	ft_get_addr(d);
}

void	ft_ray(t_data *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, 1400, 720, "Cub3D");
	ft_init(d);
	ft_get_text(d);
	mlx_hook(d->win, 33, 1L << 17, ft_cross, d);
	mlx_hook(d->win, 2, 1L << 0, key_hook, d);
	mlx_hook(d->win, 3, 1L << 0, key_hook, d);
	mlx_hook(d->win, 9, 1L << 21, render_next_frame, d);
	mlx_loop_hook(d->mlx, render_next_frame, d);
	mlx_loop(d->mlx);
}
