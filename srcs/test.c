/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/09 15:04:28 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3D.h"
#include <stdio.h>

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int     add_shade(double distance, int color)
{
    int r;
    int g;
    int b;
    
    r = (get_r(color) >> 16) * distance;
    g = (get_g(color) >> 8) * distance;
    b = (get_b(color)) * distance;
    
    color = r << 16 | g << 8 | b;
    return (color);
}

int     get_opposite(int color)
{
    int r;
    int g;
    int b;
    
    r = 255 - (get_r(color) >> 16);
    g = 255 - (get_g(color) >> 8);
    b = 255 - (get_b(color));

    color = r << 16 | g << 8 | b;
    return (color);
}

// int     main()
// {
//     int trgb;
//     int trgb2;
//     int r;

//     trgb = 0;
//     r = 0;
//     trgb2 = 0;

//     printf("trgb1 = %x\n", trgb);
    
//     trgb = create_trgb(1, 1, 1, 1);
 
//     printf("trgb2 = %x\n", trgb);
    
//     trgb = get_opposite(trgb);
//     //trgb = add_shade(0.5, trgb);
    
//     printf("trgb3 = %x\n", trgb);
    
//     return (0);
