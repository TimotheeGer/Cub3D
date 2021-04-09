/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:42:25 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/09 16:03:22 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_countlst(t_list *lst)
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

void	ft_checkisdigit(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if ((!(ft_isdigit(str[i]))) && str[i] != '-' && str[i] != ' ')
			ft_quit(0, "Error there are alphabetic characters in the data.\n");
		i++;
	}
}

int		ft_checkpara(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_checkparatextu(char *str, char *indic)
{
	if (ft_strnstr(str, indic, ft_strlen(str)))
		return (1);
	else
		return (0);
}

void	ft_get_allpara(t_para *par, t_list *lst)
{
	while (lst != NULL)
	{
		if (ft_checkpara(lst->content, 'R'))
			ft_get_r(par, lst->content);
		else if (ft_checkparatextu(lst->content, "NO"))
			ft_get_no(par, lst->content);
		else if (ft_checkparatextu(lst->content, "SO"))
			ft_get_so(par, lst->content);
		else if (ft_checkparatextu(lst->content, "WE"))
			ft_get_we(par, lst->content);
		else if (ft_checkparatextu(lst->content, "EA"))
			ft_get_ea(par, lst->content);
		else if (ft_checkpara(lst->content, 'S') && par->index.SP == 0)
			ft_get_s(par, lst->content);
		else if (ft_checkpara(lst->content, 'F'))
			ft_get_f(par, lst->content);
		else if (ft_checkpara(lst->content, 'C'))
			ft_get_c(par, lst->content);
		else if (ft_checkpara(lst->content, '1') && par->indexmap == 0)
		{
			par->indexmap = 1;
			ft_get_map(par, lst);
		}
		lst = lst->next;
	}
}
