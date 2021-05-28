/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tnave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:00:15 by tnave             #+#    #+#             */
/*   Updated: 2021/05/28 14:37:08 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_text(t_data *data, t_text *texture, int x, int y)
{
	t_text tex;
	int i;
	y = y -1;
	choose_ray(data, texture);
	tex = texture[data->texdir];
	tex.step = 1.0 * tex.height / data->ray->line_height;
	tex.tex_x = (int)(tex.wallx * (double)tex.width);
	if (data->ray->side == 0 && data->ray->ray_dir_x > 0)
		tex.tex_x = tex.width - tex.tex_x - 1;
	if (data->ray->side == 1 && data->ray->ray_dir_y < 0)
		tex.tex_x = tex.width - tex.tex_x - 1;
	tex.texpos = (y - data->ray->h / 2 + data->ray->line_height / 2) * tex.step;
	while (++y <= data->ray->draw_end)
	{
		tex.texpos += tex.step;			// increment tex.step with loot of 8.6 sprites
		tex.tex_y = (int)tex.texpos & (tex.height - 1);
		i = tex.tex_y * tex.line_length + tex.tex_x * (tex.bits_per_pixel / 8);
		if (y < data->ray->h && x < data->ray->w)
		{
			my_mlx_pixel_put(data, x, y, create_trgb(0, (int)(unsigned char)tex.addr[i + 2], (int)(unsigned char)tex.addr[i + 1], (int)(unsigned char)tex.addr[i]));
			//printf("rgb (r = %d, g = %d, b = %d\n", (int)(unsigned char)tex.addr[i], (int)(unsigned char)tex.addr[i + 1], (int)(unsigned char)tex.addr[i + 2]);
			// data->addr[y * data->line_length + x * (data->bits_per_pixel / 8)] = tex.addr[i];
		}
	}
}
void	ft_verline(int x, t_data *data, t_text *texture) // ray->x ???? too much parameters
{
	if (data->ray->draw_start < data->ray->draw_end)
	{
		draw_text(data, texture, x, data->ray->draw_start);
		data->ray->draw_start++;
	}
}

void	add_texture(t_text *texture)
{
	texture[0].addr = mlx_get_data_addr(texture[0].img,
			&texture[0].bits_per_pixel, &texture[0].line_length,
			&texture[0].endian);
	texture[1].addr = mlx_get_data_addr(texture[1].img,
			&texture[1].bits_per_pixel, &texture[1].line_length,
			&texture[1].endian);
	texture[2].addr = mlx_get_data_addr(texture[2].img,
			&texture[2].bits_per_pixel, &texture[2].line_length,
			&texture[2].endian);
	texture[3].addr = mlx_get_data_addr(texture[3].img,
			&texture[3].bits_per_pixel, &texture[3].line_length,
			&texture[3].endian);
	texture[4].addr = mlx_get_data_addr(texture[4].img,
			&texture[4].bits_per_pixel, &texture[4].line_length,
			&texture[4].endian);
}
void	ft_texture(t_data *data, t_text *texture)
{
	texture[0].img = mlx_xpm_file_to_image(data->mlx, data->no,
			&(texture[0].width), &(texture[0].height));
	if (!texture[0].img)
		ft_error(0, "Error No\n", data);
	texture[1].img = mlx_xpm_file_to_image(data->mlx, data->so,
			&(texture[1].width), &(texture[1].height));
	if (!texture[1].img)
		ft_error(0, "Error So\n", data);
	texture[2].img = mlx_xpm_file_to_image(data->mlx, data->we,
			&(texture[2].width), &(texture[2].height));
	if (!texture[2].img)
		ft_error(0, "Error We\n", data);
	texture[3].img = mlx_xpm_file_to_image(data->mlx, data->ea,
			&(texture[3].width), &(texture[3].height));
	if (!texture[3].img)
		ft_error(0, "Error Ea\n", data);
	texture[4].img = mlx_xpm_file_to_image(data->mlx, data->s,
			&(texture[4].width), &(texture[4].height));
	if (!texture[4].img)
		ft_error(0, "Error Sprites\n", data);
}