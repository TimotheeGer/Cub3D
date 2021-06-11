/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:44:00 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/09 12:59:44 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_get_no(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.NO++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "NO", 3)) || par->index.NO != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error ./path_NO.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error too much ./path_NO.\n", par);
	}
	else
		par->t_no.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_so(t_para *par, char *line)
{
	int		i;
	char	**strs;

	strs = NULL;
	i = 0;
	par->index.SO++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "SO", 3)) || par->index.SO != 1)
	{
		printf("strs[0] = %s\n", strs[0]);
		ft_free_tab(strs);
		ft_quit(0, "Error ./path_SO.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error too much ./path_SO.\n", par);
	}
	else
		par->t_so.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_we(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.WE++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "WE", 3)) || par->index.WE != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error ./path_WE.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error too much ./path_WE.\n", par);
	}
	else
		par->t_we.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_ea(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.EA++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "EA", 3)) || par->index.EA != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error ./path_EA.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error too much ./path_EA.\n", par);
	}
	else
		par->t_ea.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_s(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.SP++;
	if (par->indexmap == 1)
		ft_quit(0, "map location errors.\n", par);
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "S", 2)) || par->index.SP != 1)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error ./path_NO.\n", par);
	}	
	while (strs[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_free_tab(strs);
		ft_quit(0, "Error too much ./path_S.\n", par);
	}
	else
		par->t_sp.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}
