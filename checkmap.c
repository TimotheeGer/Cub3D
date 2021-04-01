/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:43:58 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/01 15:31:41 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void         ft_firstline_av_one(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != '1' && str[i] != ' ')
            ft_quit(0, "Missing 1 in map.\n");
        i++;
    }
}

void         ft_firstchar_is_one(char **map)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (map[y])
    {
        while (map[y][x] == ' ')
            x++;
        if (map[y][x] != '1')
            ft_quit(0,"Missing 1 in map.\n");
        while (ft_checkisNWSE201(map[y][x]))
            x++;
        if (map[y][x] != '\0')
            ft_quit(0,"Missing 1 in map.\n");
        while (map[y][x] == ' ' || map[y][x] == '\0')
            x--;
        if (map[y][x] != '1')
            ft_quit(0,"Missing 1 in map.\n");
        y++;
        x = 0;
    }
}

void         ft_checkaround(char **map, int y, int x, char c)
{
    if (map[y][x] == c && (map[y - 1][x - 1] == ' ' || map[y - 1][x - 1] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y - 1][x] == ' ' || map[y - 1][x] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y - 1][x + 1] == ' ' || map[y - 1][x + 1] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y][x - 1] == ' ' || map[y][x - 1] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y][x + 1] == ' ' || map[y][x + 1] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y + 1][x - 1] == ' ' || map[y + 1][x - 1] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y + 1][x] == ' ' || map[y + 1][x] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
    if (map[y][x] == c && (map[y + 1][x + 1] == ' ' || map[y + 1][x + 1] == '\0'))
        ft_quit(0, "The map is open, a 1 is missing.\n");
}

void        ft_mapisok(t_para *par, t_perso *perso)
{
    int i;

    i = ft_countline_map(par->map);
    
    ft_firstline_av_one(par->map[0]);
    ft_firstline_av_one(par->map[i - 1]);
    ft_firstchar_is_one(par->map);
    ft_control0(par, i, perso);
    ft_checkpos(perso);
}