/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:32:51 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 16:32:32 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_line_av_one(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_indexplus(char c, t_perso *perso, int x, int y)
{
	perso->vue = c;
	perso->pos_y = y;
	perso->pos_x = x;
	if (c == 'N')
		perso->indexno++;
	if (c == 'E')
		perso->indexea++;
	if (c == 'W')
		perso->indexwe++;
	if (c == 'S')
		perso->indexso++;
}

void	ft_control0(t_para *par, int len, t_perso *perso)
{
	int	y;
	int	x;

	y = 1;
	x = 1;
	while (par->map[y] && y < len - 1 && par->map[y][x])
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
			}
			x++;
		}
		x = 1;
		y++;
	}
}
