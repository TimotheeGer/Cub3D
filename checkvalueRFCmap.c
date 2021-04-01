/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvalueRFCmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:47:31 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/01 15:21:41 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    ft_checkisdigit(char *str)
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

void    ft_get_R(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    par->index.R++;
    while (line[i])
    {
        if (line[i] == 'R')
            strs = ft_split(&line[i + 1], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
    {
        ft_checkisdigit(strs[i]);
        i++;
    }
    if (i != 2)
        ft_quit(0, "Erreur too much data for R'\n");
    else
    {
        par->Rx = ft_atoi(strs[0]);
        par->Ry = ft_atoi(strs[1]);
    }
    if (par->Rx <= 0 || par->Ry <= 0)
        ft_quit(0, "Error too large or negative resolution.\n");
}

void    ft_get_F(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    par->index.F++;
    while (line[i])
    {
        if (line[i++] == 'F')
            strs = ft_split(&line[i], ',');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
    {
        ft_checkisdigit(strs[i]);
        i++;
    }
    if (i != 3)
        ft_quit(0, "Erreur too much data for F.\n");
    else
    {
        par->F[0] = ft_atoi(strs[0]);
        par->F[1] = ft_atoi(strs[1]);
        par->F[2] = ft_atoi(strs[2]);
    }
    i = 0;
    while (i < 3)
    {
        if (!(par->F[i] <= 255 && par->F[i] >= 0))
            ft_quit(0, "Error RGB(F).\n");
        i++;
    }
}

void    ft_get_C(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    par->index.C++;
    while (line[i])
    {
        if (line[i++] == 'C')
            strs = ft_split(&line[i], ',');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
    {
        ft_checkisdigit(strs[i]);
        i++;
    }
    if (i != 3)
        ft_quit(0, "Erreur too much data for C.\n");
    else
    {
        par->C[0] = ft_atoi(strs[0]);
        par->C[1] = ft_atoi(strs[1]);
        par->C[2] = ft_atoi(strs[2]);
    }
    i = 0;
    while (i < 3)
    {
        if (!(par->C[i] <= 255 && par->C[i] >= 0))
            ft_quit(0, "Error RGB(C).\n");
        i++;
    }
}

void    ft_get_MAP(t_para *par, t_list *lst)
{
    int i;
    
    i = 0;
    if (!(par->map = malloc(sizeof(char*) * ft_countlst(lst) + 1)))
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
