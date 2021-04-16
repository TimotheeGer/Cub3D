/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvaluerfcmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@studemt.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:47:31 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/16 16:57:11 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_checkerror_para(char **strs, int a, char c, t_para *par)
{
	int i;

	i = 1;
	if (strs == NULL)
		ft_quit(0, "Erreur no data.\n", par);
	while (strs[i] != NULL)
	{
		ft_checkisdigit(strs[i], par, strs);
		i++;
	}
	if (i != a)
	{
		ft_free_tab(strs);
		if (c == 'R')
			ft_quit(0, "Erreur too much data for R.\n", par);
		if (c == 'F')
			ft_quit(0, "Erreur too much data for F.\n", par);
		if (c == 'C')
			ft_quit(0, "Erreur too much data for C.\n", par);
	}
}

void		ft_get_r(t_para *par, char *line)
{
	char	**strs;

	strs = NULL;
	par->index.R++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "R", 2)))
	{
		ft_free_tab(strs);
		ft_quit(0, "Error no indic R.\n", par);
	}	
	ft_checkerror_para(strs, 3, 'R', par);
	par->Rx = ft_atoi(strs[1]);
	par->Ry = ft_atoi(strs[2]);
	ft_free_tab(strs);
	if (par->Rx <= 0 || par->Ry <= 0)
		ft_quit(0, "Error too large or negative resolution.\n", par);
}

void		ft_get_f(t_para *par, char *line)
{
	char	**strs;
	int 	i;

	i = 0;
	strs = NULL;
	par->index.F++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split_charset(line, ", ");
	if ((ft_strncmp(strs[0], "F", 2)))
	{
		ft_free_tab(strs);
		ft_quit(0, "Error no indic F.\n", par);
	}	
	ft_checkerror_para(strs, 4, 'F', par);
	par->F[0] = ft_atoi(strs[1]);
	par->F[1] = ft_atoi(strs[2]);
	par->F[2] = ft_atoi(strs[3]);
	ft_free_tab(strs);
	while (i < 3)
	{
		if (!(par->F[i] <= 255 && par->F[i] >= 0))
			ft_quit(0, "Error RGB(F).\n", par);
		i++;
	}
}

void		ft_get_c(t_para *par, char *line)
{
	char	**strs;
	int		i;

	i = 0;
	strs = NULL;
	par->index.C++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split_charset(line, ", ");
	if ((ft_strncmp(strs[0], "C", 2)))
	{
		ft_free_tab(strs);
		ft_quit(0, "Error no indic C.\n", par);
	}	
	ft_checkerror_para(strs, 4, 'C', par);
	par->C[0] = ft_atoi(strs[1]);
	par->C[1] = ft_atoi(strs[2]);
	par->C[2] = ft_atoi(strs[3]);
	ft_free_tab(strs);
	while (i < 3)
	{
		if (!(par->C[i] <= 255 && par->C[i] >= 0))
			ft_quit(0, "Error RGB(C).\n", par);
		i++;
	}
}

int		ft_check_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return(1);
		i++;
	}
	return (0);
}

void		ft_check_rest_lst(t_para *par, t_list *lst)
{
	while (lst)
	{
		if (ft_check_char(lst->content, ' '))
			ft_quit(0, "error to much data after map.\n", par);
		else
			lst = lst->next;
	}
}

void		ft_get_map(t_para *par, t_list *lst)
{
	int	i;

	i = 0;
	par->indexmap++;
	if (!(par->map = (char **)malloc(sizeof(char*) * (ft_countlst(lst) + 1))))
		return ;
	while (lst)
	{
		if (ft_checkpara(lst->content, '1'))
		{
			par->map[i] = ft_strdup(lst->content);
			i++;
		}
		else
		{
			par->map[i] = NULL;
			ft_check_rest_lst(par, lst);
			return ;
		}
		lst = lst->next;
	}
	par->map[i] = NULL;
}
