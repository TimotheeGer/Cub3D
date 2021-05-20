/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:32:51 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/20 16:18:26 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int			ft_line_av_one(char *line, char c)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		ft_indexplus(char c, t_perso *perso, int x, int y)
{
	perso->vue = c;
	perso->pos_y = y;
	perso->pos_x = x;
	if (c == 'N')
		perso->indexNO++;
	if (c == 'E')
		perso->indexEA++;
	if (c == 'W')
		perso->indexWE++;
	if (c == 'S')
		perso->indexSO++;
}

void		ft_control0(t_para *par, int len, t_perso *perso)
{
	int y;
	int x;

	y = 1;
	x = 1;
	while (par->map[y] && y < len -1  && par->map[y][x])
	{
		while (par->map[y][x])
		{
			if (ft_checkis0news2(par->map[y][x]))
			{
				ft_checkaround(par->map, y, x, par);
				if (ft_checkisnews(par->map[y][x]))
				{
					ft_indexplus(par->map[y][x], perso, y, x);
					par->map[y][x] = '0';
				}
				else if (par->map[y][x] == '2')
				{
					ft_lstadd_backsprite(&par->sprite, ft_newsprite(x, y));
					par->sp_begin = par->sprite;
				}
			}
			x++;
		}
		x = 1;
		y++;
	}
}
