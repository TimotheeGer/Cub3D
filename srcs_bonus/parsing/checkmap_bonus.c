/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:43:58 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 13:12:37 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_firstline_av_one(char *str, t_para *par)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			ft_quit(0, "Error\nMissing 1 in map first.\n", par);
		i++;
	}
}

void	ft_firstchar_is_one(char **map, t_para *par)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (map == NULL)
		ft_quit(0, "Error\nError Map.\n", par);
	while (map[y])
	{
		while (map[y][x] == ' ' && map[y][x])
			x++;
		if (map[y][x] != '1' && map[y][x])
			ft_quit(0, "Error\nError Map.\n", par);
		while (ft_checkisnwse201(map[y][x]))
			x++;
		if (map[y][x] != '\0' && map[y][x])
			ft_quit(0, "Error\nError Map.\n", par);
		while (map[y][x] == ' ' || map[y][x] == '\0')
			x--;
		if (map[y][x] != '1' && map[y][x])
			ft_quit(0, "Error\nError Map.\n", par);
		y++;
		x = 0;
	}
}

void	ft_checkaround(char **map, int y, int x, t_para *par)
{
	if ((map[y - 1][x - 1] == ' ' || map[y - 1][x - 1] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y - 1][x] == ' ' || map[y - 1][x] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y - 1][x + 1] == ' ' || map[y - 1][x + 1] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y][x - 1] == ' ' || map[y][x - 1] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y][x + 1] == ' ' || map[y][x + 1] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y + 1][x - 1] == ' ' || map[y + 1][x - 1] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y + 1][x] == ' ' || map[y + 1][x] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
	if ((map[y + 1][x + 1] == ' ' || map[y + 1][x + 1] == '\0'))
		ft_quit(0, "Error\nThe map is open, a 1 is missing.\n", par);
}

void	ft_mapisok(t_para *par, t_perso *perso)
{
	int	i;

	i = 0;
	i = ft_countline_map(par->map);
	ft_firstline_av_one(par->map[0], par);
	ft_firstline_av_one(par->map[i - 1], par);
	ft_firstchar_is_one(par->map, par);
	ft_control0(par, i, perso);
	ft_checkpos(perso, par);
}
