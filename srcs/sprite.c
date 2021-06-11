/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:39:08 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/11 15:03:25 by tigerber         ###   ########.fr       */
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
    // for(int i = 0; i < numSprites; i++)
    // {
      
    //     spriteOrder[i] = i;
    //     printf("spriteOrder[i] = %d\n", spriteOrder[i]);
    //     printf("spriteDistance[i] = %f\n", spriteDistance[i]);
    //     printf("spx = %d\n", d->par.sprite->sp_x);
    //     printf("spy = %d\n", d->par.sprite->sp_y);
    //     spriteDistance[i] = (double)((d->x - d->par.sprite->sp_x) * (d->x - d->par.sprite->sp_x) + (d->y - d->par.sprite->sp_y) * (d->y - d->par.sprite->sp_y)); //sqrt not taken, unneeded
    //     printf("test2\n");   
    // }
    //sortSprites(spriteOrder, spriteDistance, numSprites);

    //after sorting the sprites, do the projection and draw them
for(int i = 0; i < numSprites; i++)
{ 

      //translate sprite position to relative to camera
    double spriteX = d->par.sprite->sp_x - d->x;
    double spriteY = d->par.sprite->sp_y - d->y;
          printf("test5\n");

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (d->planeX * d->dy - d->dx * d->planeY); //required for correct matrix multiplication

      double transformX = invDet * (d->dy * spriteX - d->dx * spriteY);
      double transformY = invDet * (-d->planeY * spriteX + d->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

      int spriteScreenX = (int)((d->par.Rx / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(d->par.Ry / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + d->par.Ry / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + d->par.Ry / 2 + vMoveScreen;
      if(drawEndY >= d->par.Ry) drawEndY = d->par.Ry - 1;

      //calculate width of the sprite
      int spriteWidth = abs((int)(d->par.Ry / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= d->par.Rx) drawEndX = d->par.Rx - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {

        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * d->par.t_sp.width / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < d->par.Rx)
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int c = (y-vMoveScreen) * 256 - d->par.Ry * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((c * d->par.t_sp.heigth) / spriteHeight) / 256;
          int j = texY * d->par.t_sp.line_len + texX * 4; 
          int color = create_trgb(0, (int)(unsigned char)d->par.t_sp.addr[j + 2],
                                    (int)(unsigned char)d->par.t_sp.addr[j + 1],
                                    (int)(unsigned char)d->par.t_sp.addr[j]); 
            my_mlx_pixel_put(&d->screen, stripe, y, color);
          
        //   Uint32 color = texture[sprite[spriteOrder[i]].texture][d->par.t_sp.width * texY + texX]; //get current color from the texture
        //   if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }
}