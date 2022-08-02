/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvaluerfcmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:47:31 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:47:25 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_checkerror_para(char **strs, int a, char c, t_para *par)
{
	int	i;

	i = 1;
	if (strs == NULL)
		ft_quit(0, "Error\nErreur no data.\n", par);
	while (strs[i] != NULL)
	{
		ft_checkisdigit(strs[i], par, strs);
		i++;
	}
	if (i != a)
	{
		ft_free_tab(strs);
		if (c == 'R')
			ft_quit(0, "Error\nErreur too much data for R.\n", par);
		if (c == 'F')
			ft_quit(0, "Error\nErreur too much data for F.\n", par);
		if (c == 'C')
			ft_quit(0, "Error\nErreur too much data for C.\n", par);
	}
}

void	ft_get_f(t_para *par, char *line)
{
	char	**strs;
	int		i;

	i = 0;
	strs = NULL;
	par->index.f++;
	if (par->indexmap == 1)
		ft_quit(0, "Error\nmap location errors.\n", par);
	strs = ft_split_charset(line, ", ");
	if ((ft_strncmp(strs[0], "F", 2)))
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError no indic F.\n", par);
	}	
	ft_checkerror_para(strs, 4, 'F', par);
	par->fl[0] = ft_atoi(strs[1]);
	par->fl[1] = ft_atoi(strs[2]);
	par->fl[2] = ft_atoi(strs[3]);
	ft_free_tab(strs);
	while (i < 3)
	{
		if (!(par->fl[i] <= 255 && par->fl[i] >= 0))
			ft_quit(0, "Error\nError RGB(F).\n", par);
		i++;
	}
}

void	ft_get_c(t_para *par, char *line)
{
	char	**strs;
	int		i;

	i = 0;
	strs = NULL;
	par->index.c++;
	if (par->indexmap == 1)
		ft_quit(0, "Error\nmap location errors.\n", par);
	strs = ft_split_charset(line, ", ");
	if ((ft_strncmp(strs[0], "C", 2)))
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError no indic C.\n", par);
	}	
	ft_checkerror_para(strs, 4, 'C', par);
	par->ci[0] = ft_atoi(strs[1]);
	par->ci[1] = ft_atoi(strs[2]);
	par->ci[2] = ft_atoi(strs[3]);
	ft_free_tab(strs);
	while (i < 3)
	{
		if (!(par->ci[i] <= 255 && par->ci[i] >= 0))
			ft_quit(0, "Error\nError RGB(C).\n", par);
		i++;
	}
}

void	ft_check_rest_lst(t_para *par, t_list *lst)
{
	while (lst)
	{
		if (ft_check_char(lst->content, ' '))
			ft_quit(0, "Error\nerror map.\n", par);
		else
			lst = lst->next;
	}
}

void	ft_get_map(t_para *par, t_list *lst)
{
	int	i;

	i = 0;
	par->indexmap++;
	par->map = (char **)malloc (sizeof (char *) * (ft_countlst (lst) + 1));
	if (!(par->map))
		ft_quit (0, "Error\nerror map.\n", par);
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
