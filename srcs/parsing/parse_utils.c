/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:42:25 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/11 14:01:08 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_checkisdigit(char *s, t_para *par, char **strs)
{
	int	i;

	i = 0;
	if (ft_strlen(s) > 10)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError RGB.\n", par);
	}
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if ((!(ft_isdigit(s[i]))) && s[i] != ' ' && s[i] != '\t')
		{
			ft_free_tab(strs);
			ft_quit(0, "Error\nError there are alphabetic characters.\n", par);
		}
		i++;
	}
}

int	ft_checkpara(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == c)
		return (1);
	return (0);
}

int	ft_checkparatextu(char *str, char *indic)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == indic[0] && str[i + 1] == indic[1])
		return (1);
	return (0);
}

int	check_line_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((str[i] == '\0') || (str[i] == 'N' && str[i + 1] == 'O')
		|| (str[i] == 'S' && str[i + 1] == 'O')
		|| (str[i] == 'W' && str[i + 1] == 'E')
		|| (str[i] == 'E' && str[i + 1] == 'A')
		|| (str[i] == 'F')
		|| (str[i] == 'C')
		|| (str[i] == '1'))
		return (0);
	return (1);
}

void	ft_get_allpara(t_para *par, t_list *lst)
{
	while (lst != NULL)
	{
		if (ft_checkparatextu(lst->content, "NO"))
			ft_get_no(par, lst->content);
		else if (ft_checkparatextu(lst->content, "SO"))
			ft_get_so(par, lst->content);
		else if (ft_checkparatextu(lst->content, "WE"))
			ft_get_we(par, lst->content);
		else if (ft_checkparatextu(lst->content, "EA"))
			ft_get_ea(par, lst->content);
		else if (ft_checkpara(lst->content, 'F'))
			ft_get_f(par, lst->content);
		else if (ft_checkpara(lst->content, 'C'))
			ft_get_c(par, lst->content);
		else if (ft_checkpara(lst->content, '1') && par->indexmap == 0)
			ft_get_map(par, lst);
		else if (check_line_valid(lst->content))
			ft_quit(0, "Error\nError invalid data.\n", par);
		lst = lst->next;
	}
}
