/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:41:22 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/11 15:14:24 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define screenWidth 1080
#define screenHeight 920
#define mapWidth 24
#define mapHeight 24

//###############################################################################

//dessine les lisgne vertical//

void	drawverticalline(t_data *data, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		my_mlx_pixel_put(&data->screen, x, drawstart, color);
		drawstart++;
	}
}

//###############################################################################
void    init_floor_one(t_data *d)
{
    d->f.x = 0;
    d->f.raydirx0 = d->dx - d->planeX;
    d->f.raydiry0 = d->dy - d->planeY;
    d->f.raydirx1 = d->dx + d->planeX;
    d->f.raydiry1 = d->dy + d->planeY;
    d->f.p = d->f.y - d->par.Ry / 2;
    d->f.posz = 0.5 * d->par.Ry;
    d->f.rowdistance = d->f.posz / d->f.p;
    d->f.floorstepx = d->f.rowdistance * (d->f.raydirx1 - d->f.raydirx0) / d->par.Rx;
    d->f.floorstepy = d->f.rowdistance * (d->f.raydiry1 - d->f.raydiry0) / d->par.Rx;
    d->f.floorx = d->x + d->f.rowdistance * d->f.raydirx0;
    d->f.floory = d->y + d->f.rowdistance * d->f.raydiry0;
}

// void    init_floor_two(t_data *d)
// {
  
// }

void    ft_floor(t_data *d)
{
    d->f.y = d->f.h / 2 + 1;
    while (d->f.y < d->par.Ry)
    {
      d->f.y++;
      init_floor_one(d);
      while( d->f.x < d->par.Rx)
      { 
        d->f.x++;
        int cellX = (int)(d->f.floorx);
        int cellY = (int)(d->f.floory);
        
        int tx = (int)( d->par.t_sol.width * (d->f.floorx - cellX)) & (d->par.t_sol.width - 1);
        int ty = (int)(d->par.t_sol.heigth * (d->f.floory - cellY)) & (d->par.t_sol.heigth - 1);

        d->f.floorx += d->f.floorstepx;
        d->f.floory += d->f.floorstepy;

        int i = ty * d->par.t_sol.line_len + tx * 4;
        int color;
        color = create_trgb(0, (int)(unsigned char)d->par.t_sol.addr[i + 2],
                                    (int)(unsigned char)d->par.t_sol.addr[i + 1],
                                    (int)(unsigned char)d->par.t_sol.addr[i]); 
        my_mlx_pixel_put(&d->screen, d->f.x, d->f.y, color);
         
      }
      
    }
}



void    raycaster(t_data *data)
{
    int x = 0;
    int w = data->par.Rx;
    int h = data->par.Ry;
    
        //calculate ray position and direction
      
    
    ft_floor(data);

    while (x<w)
    {
      double cameraX = 2.0 * x / (double)w - 1.0; //x-coordinate in camera space
      double rayDirX = data->dx + data->planeX * cameraX;
      double rayDirY = data->dy + data->planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)data->x;
      int mapY = (int)data->y;

      //length of ray from current position to next x or y-side
      double sideDistX = 0;
      double sideDistY = 0;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist = 0;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX = 0;
      int stepY = 0;

      int hit = 0; //was there a wall hit?
      int side = 0; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (data->x - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->x) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (data->y - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->y) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (data->par.map[mapX][mapY] == '1') 
          hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0)
      {
        perpWallDist = (mapX - data->x + (1 - stepX) / 2) / rayDirX;
      }
      else
        perpWallDist = (mapY - data->y + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;
      
      //texturing calculations
          //calculate value of wallX
      double wallX; //where exactly the wall was hit
      double step = 1.0 * 512 / lineHeight;
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      if(side == 0)
          wallX = data->y + perpWallDist * rayDirY;
      else
          wallX = data->x + perpWallDist * rayDirX;
      wallX -= floor((wallX));
      
      int texX = (int)(wallX * (double)512);
      if(side == 0 && rayDirX > 0)
          texX = 512 - texX - 1;
      if(side == 1 && rayDirY < 0)
          texX = 512 - texX - 1;


      for(int y = drawStart ; y <= drawEnd; y++)
      {
          int texY = (int)texPos & (512 - 1);
          texPos += step;
          int i = texY * 2048 + texX * 4;
          int color = 0;
          if (y < h && x < w)
          {
              if (side == 0 && rayDirX < 0) // nord
              {
                color = create_trgb(0, (int)(unsigned char)data->par.t_no.addr[i + 2],
                                    (int)(unsigned char)data->par.t_no.addr[i + 1],
                                    (int)(unsigned char)data->par.t_no.addr[i]); 
              }
              if (side == 0 && rayDirX > 0) // sud
              {
                 color = create_trgb(0, (int)(unsigned char)data->par.t_so.addr[i + 2],
                                    (int)(unsigned char)data->par.t_so.addr[i + 1],
                                    (int)(unsigned char)data->par.t_so.addr[i]); 
              }
              if (side == 1 && rayDirY > 0) // east
              {
                color = create_trgb(0, (int)(unsigned char)data->par.t_ea.addr[i + 2],
                                    (int)(unsigned char)data->par.t_ea.addr[i + 1],
                                    (int)(unsigned char)data->par.t_ea.addr[i]); 
              }
              if (side == 1 && rayDirY < 0) //west
              {
                color = create_trgb(0, (int)(unsigned char)data->par.t_we.addr[i + 2],
                                    (int)(unsigned char)data->par.t_we.addr[i + 1],
                                    (int)(unsigned char)data->par.t_we.addr[i]); 
              }
              my_mlx_pixel_put(&data->screen, x, y, color);
          }
      }
      x++;
    }
    
    #define numSprites 1
    // int spriteOrder[numSprites];
    // double spriteDistance[numSprites];
    
    for(int i = 0; i < numSprites; i++)
    { 

      //translate sprite position to relative to camera
      double spriteX = data->par.sprite->sp_x - data->x;
      double spriteY = data->par.sprite->sp_y - data->y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (data->planeX * data->dy - data->dx * data->planeY); //required for correct matrix multiplication

      double transformX = invDet * (data->dy * spriteX - data->dx * spriteY);
      double transformY = invDet * (-data->planeY * spriteX + data->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

      int spriteScreenX = (int)((data->par.Rx / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(data->par.Ry / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + data->par.Ry / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + data->par.Ry / 2 + vMoveScreen;
      if(drawEndY >= data->par.Ry) drawEndY = data->par.Ry - 1;

      //calculate width of the sprite
      int spriteWidth = abs((int)(data->par.Ry / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= data->par.Rx) drawEndX = data->par.Rx - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {

        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->par.t_sp.width / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < data->par.Rx)
        {
          for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
          {

            int c = (y-vMoveScreen) * 256 - data->par.Ry * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
            int texY = ((c * data->par.t_sp.heigth) / spriteHeight) / 256;
            if (data->par.t_sp.addr[texY * data->par.t_sp.line_len + texX * (data->par.t_sp.b_p_pix / 8)])
            {  
              int j = texY * data->par.t_sp.line_len + texX * 4; 
              int color = create_trgb(0, (int)(unsigned char)data->par.t_sp.addr[j + 2],
                                    (int)(unsigned char)data->par.t_sp.addr[j + 1],
                                    (int)(unsigned char)data->par.t_sp.addr[j]); 
              my_mlx_pixel_put(&data->screen, stripe, y, color);
            }
          }
        //   Uint32 color = texture[sprite[spriteOrder[i]].texture][d->par.t_sp.width * texY + texX]; //get current color from the texture
        //   if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }
    
}