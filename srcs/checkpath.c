/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:44:00 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/14 16:30:03 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_get_no(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.NO++;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O')
		{
			strs = ft_split(&line[i + 2], ' ');
			break;
		}
		i++;
	}
	i = 0;
	while (strs[i] != NULL)
		i++;
	if (i != 1)
		ft_quit(0, "Error too much ./path_NO.\n", par);
	else
		par->textNO.path = ft_strdup(strs[0]);
	ft_free_tab(strs);
}

void		ft_get_so(t_para *par, char *line)
{
	int		i;
	char	**strs;

	strs = NULL;
	i = 0;
	par->index.SO++;
	if (line[i] == 'S' && line[i + 1] == 'O')
		strs = ft_split(&line[i + 2], ' ');
	i = 0;
	while (strs[i] != NULL)
		i++;
	if (i != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error too much ./path_SO.\n", par);
	}
	else
		par->textSO.path = ft_strdup(strs[0]);
	ft_free_tab(strs);
}
//fix problem de split en dessous
void		ft_get_we(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.WE++;
	while (line[i])
	{
		if (line[i] == 'W' && line[i + 1] == 'E')
			strs = ft_split(&line[i + 2], ' ');
		i++;
	}
	i = 0;
	while (strs[i] != NULL)
		i++;
	if (i != 1)
		ft_quit(0, "Error too much ./path_WE.\n", par);
	else
		par->textWE.path = ft_strdup(strs[0]);
	ft_free_tab(strs);
}

void		ft_get_ea(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.EA++;
	while (line[i])
	{
		if (line[i] == 'E' && line[i + 1] == 'A')
			strs = ft_split(&line[i + 2], ' ');
		i++;
	}
	i = 0;
	while (strs[i] != NULL)
		i++;
	if (i != 1)
		ft_quit(0, "Error too much ./path_EA.\n", par);
	else
		par->textEA.path = ft_strdup(strs[0]);
	ft_free_tab(strs);
}

void		ft_get_s(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.SP++;
	while (line[i])
	{
		if (line[i] == 'S')
			strs = ft_split(&line[i + 1], ' ');
		i++;
	}
	i = 0;
	while (strs[i] != NULL)
		i++;
	if (i != 1)
		ft_quit(0, "Error too much ./path_S.\n", par);
	else
		par->textSp.path = ft_strdup(strs[0]);
	ft_free_tab(strs);
}
