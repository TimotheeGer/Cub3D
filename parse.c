/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:12:56 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/26 16:03:25 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     ft_quit(void)
{
    exit(0);
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

void    ft_get_R(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'R')
            strs = ft_split(&line[i], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 2)
        ft_quit();
    else
    {
        par->Rx = ft_atoi(strs[0]);
        par->Ry = ft_atoi(strs[1]);
    }
    if (par->Rx < 0 || par->Ry < 0)
        ft_quit();
}

void    ft_get_F(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'F')
            strs = ft_split(&line[i], ',');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 3)
        ft_quit();
    else
    {
        par->F[0] = ft_atoi(strs[0]);
        par->F[1] = ft_atoi(strs[1]);
        par->F[2] = ft_atoi(strs[2]);
    }
    i = 0;
    while (i++ < 3)
        if (!(par->F[i] <= 255 || par->F[i] >= 0))
            ft_quit();
}

void    ft_get_C(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'C')
            strs = ft_split(&line[i], ',');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 3)
        ft_quit();
    else
    {
        par->C[0] = ft_atoi(strs[0]);
        par->C[1] = ft_atoi(strs[1]);
        par->C[2] = ft_atoi(strs[2]);
    }
    i = 0;
    while (i++ < 3)
        if (!(par->C[i] <= 255 || par->C[i] >= 0))
            ft_quit();
}

void    ft_get_NO(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'N' && line[i++] == 'O')
            strs = ft_split(&line[i], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 1)
        ft_quit();
    else
        par->textNO.path = ft_strdup(strs[0]);
}

void    ft_get_SO(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'S' && line[i++] == 'O')
            strs = ft_split(&line[i], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 1)
        ft_quit();
    else
        par->textSO.path = ft_strdup(strs[0]);
}

void    ft_get_WE(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'W' && line[i++] == 'E')
            strs = ft_split(&line[i], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 1)
        ft_quit();
    else
        par->textWE.path = ft_strdup(strs[0]);
}

void    ft_get_EA(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'E' && line[i++] == 'A')
            strs = ft_split(&line[i], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 1)
        ft_quit();
    else
        par->textEA.path = ft_strdup(strs[0]);
}

void    ft_get_S(t_para *par, char *line)
{
    int i;
    char **strs;

    i = 0;
    while (line[i])
    {
        if (line[i++] == 'S')
            strs = ft_split(&line[i], ' ');
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
        i++;
    if (i != 1)
        ft_quit();
    else
        par->textSp.path = ft_strdup(strs[0]);
}

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
    int i = 0;
}

int     main()
{
    t_para  par;
    t_list  *lst;
    char *line;
    int fd = 0;
    fd = open("map.cub", O_RDONLY);
    line = NULL;
    lst = NULL;
    ft_memset(&par, 0, sizeof(t_para));
    while (get_next_line(fd, &line))
    {
        ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
        //free(line);
    }
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
    //free(line);
    ft_get_allpara(&par, &lst);

    printf("R = [%d] [%d]\n", par.Rx, par.Ry);
    printf("F = [%d] [%d] [%d]\n", par.F[0], par.F[1], par.F[2]);
    printf("C = [%d] [%d] [%d]\n", par.C[0], par.C[1], par.C[2]);
    printf("textno = [%s]\n", par.textNO.path);
    printf("textSO = [%s]\n", par.textSO.path);
    printf("textWE = [%s]\n", par.textWE.path);
    printf("textEA = [%s]\n", par.textSO.path); 
    printf("textSP = [%s]\n", par.textSp.path);    
    int i = 0;
    while (par.map[i] != NULL)
    {
        printf("map = %s\n", par.map[i]);
        i++;
    }
    // t_list *temp;
    // temp = lst;
    // while (temp->next != NULL)
    // {
    //     temp = temp->next;
    //     printf("content = %s\n", temp->content);
    // }
    return 0;
}