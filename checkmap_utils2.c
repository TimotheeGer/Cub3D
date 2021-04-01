/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:32:51 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/01 15:01:37 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void        ft_indexplus(char c, t_perso *perso, int y, int x)
{
    perso->vue = c;
    perso->pos_y = y;
    perso->pos_x = x;
    if (c == 'N')
        perso->indexNO++;
    if (c == 'E')
        perso->indexEA++;
    if (c == 'W')
        perso->indexWE++;
    if (c == 'S')
        perso->indexNO++;
}

void        ft_control0(t_para *par, int len, t_perso *perso)
{
    int y;
    int x;

    y = 1;
    x = 1;
    
    while (par->map[y] && y < len)
    {
        while (par->map[y][x])
        {
            if (ft_checkis0NEWS2(par->map[y][x]))
            {
                ft_checkaround(par->map, y, x, par->map[y][x]);
                if (ft_checkisNEWS(par->map[y][x]))
                {
                    ft_indexplus(par->map[y][x], perso, y, x);
                    par->map[y][x] = '0';
                }
                if (par->map[y][x] == '2')
                {
                    ft_lstadd_backsprite(&par->sprite, ft_newsprite(x, y));
                } 
            }
            x++;
        }
        x = 0;
        y++;
    }
}