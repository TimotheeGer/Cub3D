/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvaluerfcmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:47:31 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/14 15:18:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_checkerror_para(char **strs, int a, char c)
{
	int i;

	i = 0;
	if (strs == NULL)
		ft_quit(0, "test\n");
	while (strs[i] != NULL)
	{
		ft_checkisdigit(strs[i]);
		i++;
	}
	if (i != a)
	{
		ft_free_tab(strs);
		if (c == 'R')
			ft_quit(0, "Erreur too much data for R.\n");
		if (c == 'F')
			ft_quit(0, "Erreur too much data for F.\n");
		if (c == 'C')
			ft_quit(0, "Erreur too much data for C.\n");
	}
}

void		ft_get_r(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	strs = NULL;
	par->index.R++;
	while (line[i])
	{
		if (line[i] == 'R')
			strs = ft_split(&line[i + 1], ' ');
		i++;
	}
	ft_checkerror_para(strs, 2, 'R');
	par->Rx = ft_atoi(strs[0]);
	par->Ry = ft_atoi(strs[1]);
	ft_free_tab(strs);
	if (par->Rx <= 0 || par->Ry <= 0)
		ft_quit(0, "Error too large or negative resolution.\n");
}

void		ft_get_f(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	strs = NULL;
	par->index.F++;
	while (line[i])
	{
		if (line[i] == 'F')
			strs = ft_split_charset(&line[i + 1], ", ");
		i++;
	}
	ft_checkerror_para(strs, 3, 'F');
	par->F[0] = ft_atoi(strs[0]);
	par->F[1] = ft_atoi(strs[1]);
	par->F[2] = ft_atoi(strs[2]);
	ft_free_tab(strs);
	i = 0;
	while (i < 3)
	{
		if (!(par->F[i] <= 255 && par->F[i] >= 0))
			ft_quit(0, "Error RGB(F).\n");
		i++;
	}
}

void		ft_get_c(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	strs = NULL;
	par->index.C++;
	while (line[i])
	{
		if (line[i] == 'C')
			strs = ft_split_charset(&line[i + 1], ", ");
		i++;
	}
	ft_checkerror_para(strs, 3, 'C');
	par->C[0] = ft_atoi(strs[0]);
	par->C[1] = ft_atoi(strs[1]);
	par->C[2] = ft_atoi(strs[2]);
	ft_free_tab(strs);
	i = 0;
	while (i < 3)
	{
		if (!(par->C[i] <= 255 && par->C[i] >= 0))
			ft_quit(0, "Error RGB(C).\n");
		i++;
	}
}

void		ft_get_map(t_para *par, t_list *lst)
{
	int	i;

	i = 0;
	if (!(par->map = (char **)malloc(sizeof(char*) * (ft_countlst(lst) + 1))))
		return ;
	while (lst)
	{
		if (ft_checkpara(lst->content, '1'))
		{
			par->map[i] = ft_strdup(lst->content);
			i++;
		}
		lst = lst->next;
	}
	par->map[i] = NULL;
}
