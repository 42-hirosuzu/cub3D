/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:21:26 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/09 16:21:36 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rectangle(int x, int y, t_map *data, uint32_t color)
{
	int	i;
	int	j;

	i = x;
	j = y;
	while (y < data->size_shape + j)
	{
		x = i;
		while (x < data->size_shape + i)
		{
			mlx_put_pixel(data->img_map, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map_2(t_map *data, int mode, int i, int j)
{
	if (data->map[j][i] == '1')
		draw_rectangle(i * data->size_shape, j * data->size_shape, data,
			0xFFFFFFFF);
	if (data->map[j][i] == '0' || (mode == 0 && data->map[j][i] == 'P'))
		draw_rectangle(i * data->size_shape, j * data->size_shape, data,
			0x000000FF);
	if (data->map[j][i] == ' ')
		draw_rectangle(i * data->size_shape, j * data->size_shape, data,
			0xFF000033);
	if (data->map[j][i] == 'P' && mode)
	{
		draw_rectangle(i * data->size_shape, j * data->size_shape, data,
			0x000000FF);
		mlx_put_pixel(data->img, data->px = (i * data->size_shape)
			+ (data->size_shape / 2),
			data->py = (j * data->size_shape)
			+ (data->size_shape / 2), 0xFF0000FF);
	}
}

void	draw_map(t_cub3d *data, int mode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < data->map.height_map)
	{
		i = 0;
		while (i < data->map.width_map)
		{
			draw_map_2(&(data->map), mode, i, j);
			i++;
		}
		j++;
	}
}

void	draw_view_angle(t_cub3d *data)
{
	int		i;
	float	ray_angle;
	int		id_ray;

	i = 0;
	ray_angle = data->player.angle - (VIEW_ANGLE / 2);
	if (ray_angle < 0)
		ray_angle = 360 + ray_angle;
	id_ray = 0;
	while (i < data->render.number_rays)
	{
		if (ray_angle >= 360)
			ray_angle -= 360;
		check_ray_draw(data, ray_angle, id_ray);
		id_ray++;
		ray_angle += (VIEW_ANGLE / data->render.number_rays);
		i++;
	}
}

void	draw_ceil_floor(t_cub3d *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < HEIGHT_WIN)
	{
		i = 0;
		while (i < WIDTH_WIN)
		{
			if (j < HEIGHT_WIN / 2)
				mlx_put_pixel(data->map.img, i, j, data->textures.sky_hex);
			else
				mlx_put_pixel(data->map.img, i, j, data->textures.floor_hex);
			i++;
		}
		j++;
	}
}
