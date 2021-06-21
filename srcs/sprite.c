/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:39:08 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/21 13:45:15 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define numSprites 1
int spriteOrder[numSprites];
double spriteDistance[numSprites];

void    ft_sprite(t_data *d)
{
    for(int i = 0; i < numSprites; i++)
    { 
      double spriteX = d->par.sprite->sp_x - d->x;
      double spriteY = d->par.sprite->sp_y - d->y;

      double invDet = 1.0 / (d->planeX * d->dy - d->dx * d->planeY); 

      double transformX = invDet * (d->dy * spriteX - d->dx * spriteY);
      double transformY = invDet * (-d->planeY * spriteX + d->planeX * spriteY); 

      int spriteScreenX = (int)((d->par.Rx / 2) * (1 + transformX / transformY));

      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      int spriteHeight = abs((int)(d->par.Ry / (transformY))) / vDiv;
      int drawStartY = -spriteHeight / 2 + d->par.Ry / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + d->par.Ry / 2 + vMoveScreen;
      if(drawEndY >= d->par.Ry) drawEndY = d->par.Ry - 1;

      int spriteWidth = abs((int)(d->par.Ry / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= d->par.Rx) drawEndX = d->par.Rx - 1;

      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * d->par.t_sp.width / spriteWidth) / 256;
    
        if(transformY > 0 && stripe > 0 && stripe < d->par.Rx)
        {
          for(int y = drawStartY; y < drawEndY; y++) 
          {

            int c = (y-vMoveScreen) * 256 - d->par.Ry * 128 + spriteHeight * 128; 
            int texY = ((c * d->par.t_sp.heigth) / spriteHeight) / 256;
            if (d->par.t_sp.addr[texY * d->par.t_sp.line_len + texX * (d->par.t_sp.b_p_pix / 8)])
            {  
              int j = texY * d->par.t_sp.line_len + texX * 4; 
              int color = create_trgb(0, (int)(unsigned char)d->par.t_sp.addr[j + 2],
                                    (int)(unsigned char)d->par.t_sp.addr[j + 1],
                                    (int)(unsigned char)d->par.t_sp.addr[j]); 
              my_mlx_pixel_put(&d->screen, stripe, y, color);
            }
          }
        }
      }
    }
}