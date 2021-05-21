/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tnave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:00:15 by tnave             #+#    #+#             */
/*   Updated: 2021/05/21 18:17:25 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	ft_screen(t_data *data)
{
	int		x;
	int		y;
	int		floor;
	int		ceiling;
	x = 0;
	y = 0;
	floor = my_create_trgb(data->floor);
	ceiling = my_create_trgb(data->ceilling);
	while (y < data->res_two)
	{
		x = 0;
		while (x < data->res_one)
		{
			my_mlx_pixel_put(data, x, y, floor);
			if (y <= data->res_two / 2)
				my_mlx_pixel_put(data, x, y, ceiling);
			x++;
		}
		y++;
	}
}
void	ray_casting_first(t_ray *ray)
{
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
}
void	ray_casting_two(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}
void	dda_calcul(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}
void	ray_casting_last(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_height = (int)(ray->h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + ray->h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + ray->h / 2;
	if (ray->draw_end >= ray->h)
		ray->draw_end = ray->h - 1;
}
void	ray_lodev(t_data *data, t_text *texture)
{
	int		x;
	x = 0;
	while (x < data->ray->w)
	{
		data->ray->camera_x = 2.0 * x / (double)data->ray->w - 1.0;
		ray_casting_first(data->ray);
		ray_casting_two(data->ray);
		dda_calcul(data->ray, data);
		ray_casting_last(data->ray);
		ft_verline(x, data, texture);
		x++;
	}
}