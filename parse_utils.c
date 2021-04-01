/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:42:25 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/01 14:45:32 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int     ft_countlst(t_list *lst)
{
    int i;
    
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

int     ft_checkpara(char *str, char c)
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

int     ft_checkparatextu(char *str, char *indic)
{
    if (ft_strnstr(str, indic, ft_strlen(str)))
        return (1);
    else
        return (0);
}

void    ft_get_allpara(t_para *par, t_list **lst)
{
    t_list *temp;
    temp = *lst;
    while (temp != NULL)
    {
        if (ft_checkpara(temp->content, 'R'))
            ft_get_R(par, temp->content);
        else if (ft_checkparatextu(temp->content, "NO"))
            ft_get_NO(par, temp->content);
        else if (ft_checkparatextu(temp->content, "SO"))
            ft_get_SO(par, temp->content);
        else if (ft_checkparatextu(temp->content, "WE"))
            ft_get_WE(par, temp->content);
        else if (ft_checkparatextu(temp->content, "EA"))
            ft_get_EA(par, temp->content);
        else if (ft_checkpara(temp->content, 'S'))
            ft_get_S(par, temp->content);        
        else if (ft_checkpara(temp->content, 'F'))
            ft_get_F(par, temp->content);
        else if (ft_checkpara(temp->content, 'C'))
            ft_get_C(par, temp->content);
        else if (ft_checkpara(temp->content, '1') && par->indexmap == 0)
        {
            par->indexmap = 1;
            ft_get_MAP(par, temp);
        }
        temp = temp->next;
    }
}