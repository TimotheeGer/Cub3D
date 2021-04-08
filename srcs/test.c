/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:09:29 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/08 13:41:45 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb && (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb && (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb && (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb && 0xFF);
}

int     add_shade(double distance, int color)
{
    
}

int     main()
{
    create_trgb()
    return (0);
}