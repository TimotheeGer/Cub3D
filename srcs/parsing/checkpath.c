/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:44:00 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:43:02 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_get_no(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.no++;
	if (par->indexmap == 1)
		ft_quit(0, "Error\nmap location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "NO", 3)) || par->index.no != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError ./path_NO.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError too much ./path_NO.\n", par);
	}
	else
		par->t_no.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void	ft_get_so(t_para *par, char *line)
{
	int		i;
	char	**strs;

	strs = NULL;
	i = 0;
	par->index.so++;
	if (par->indexmap == 1)
		ft_quit(0, "Error\nmap location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "SO", 3)) || par->index.so != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError ./path_SO.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError too much ./path_SO.\n", par);
	}
	else
		par->t_so.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void	ft_get_we(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.we++;
	if (par->indexmap == 1)
		ft_quit(0, "Error\nmap location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "WE", 3)) || par->index.we != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError ./path_WE.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError too much ./path_WE.\n", par);
	}
	else
		par->t_we.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void	ft_get_ea(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.ea++;
	if (par->indexmap == 1)
		ft_quit(0, "Error\nmap location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "EA", 3)) || par->index.ea != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError ./path_EA.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error\nError too much ./path_EA.\n", par);
	}
	else
		par->t_ea.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}
