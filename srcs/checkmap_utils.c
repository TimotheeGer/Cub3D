/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:30:04 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/09 13:33:39 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_checkisnwse201(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E'
			|| c == '2' || c == '0' || c == '1' || c == ' ');
}

int		ft_checkis0news2(char c)
{
	return (c == '0' || c == 'N' || c == 'E' || c == 'W'
			|| c == 'S' || c == '2');
}

int		ft_checkisnews(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

int		ft_countline_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

void	ft_checkpos(t_perso *perso)
{
	int i;

	i = 0;
	i = perso->indexNO + perso->indexEA + perso->indexSO + perso->indexWE;
	if (i != 1)
		ft_quit(0, "Error missing or more than one character in the map.\n");
}
