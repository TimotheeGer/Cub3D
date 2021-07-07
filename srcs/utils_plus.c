/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:35:41 by tigerber          #+#    #+#             */
/*   Updated: 2021/07/07 15:11:43 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_countlst(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (ft_checkpara(lst->content, '1'))
		{
			lst = lst->next;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	full_screen_bicolor(t_data *d)
{
	d->s.x = 0;
	d->s.y = 0;
	d->s.color = d->colorC;
	while (d->s.y < d->par.Ry / 2)
	{
		while (d->s.x < d->par.Rx)
		{
			my_mlx_pixel_put(&d->screen, d->s.x, d->s.y, d->s.color);
			d->s.x++;
		}
		if (d->s.y % 4 == 0)
			d->s.color++;
		d->s.x = 0;
		d->s.y++;
	}
	while (d->s.y < d->par.Ry)
	{
		while (d->s.x < d->par.Rx)
		{
			my_mlx_pixel_put(&d->screen, d->s.x, d->s.y, d->colorF);
			d->s.x++;
		}
		d->s.x = 0;
		d->s.y++;
	}
}

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
		data->planeX = 0.66;
}
