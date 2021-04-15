/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@studemt.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:44:00 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/15 16:11:31 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
//*************fix par->index.NO != 1*************
void		ft_get_no(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.NO++;
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
		par->textNO.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_so(t_para *par, char *line)
{
	int		i;
	char	**strs;

	strs = NULL;
	i = 0;
	par->index.SO++;
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "SO", 3)))
	{
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
		par->textSO.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}
//fix problem de split en dessous
void		ft_get_we(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.WE++;
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "WE", 3)))
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
		par->textWE.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_ea(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.EA++;
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "EA", 3)))
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
		par->textEA.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}

void		ft_get_s(t_para *par, char *line)
{
	int		i;
	char	**strs;

	i = 0;
	par->index.SP++;
	strs = ft_split(line, ' ');
	if ((ft_strncmp(strs[0], "S", 2)))
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
		par->textSp.path = ft_strdup(strs[1]);
	ft_free_tab(strs);
}
