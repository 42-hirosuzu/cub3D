/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:00:07 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/18 20:53:01 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_vec(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player->pos_y) * ray->delta_dist_y;
	}
}

void	dda(t_cub3d *data, char **map)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->ray.map_x <= 0 || data->ray.map_x >= data->map.width_map \
			|| data->ray.map_y <= 0 || data->ray.map_y >= data->map.height_map)
		{
			printf("Out of map bounds: map_x=%d, map_y=%d\n", \
				data->ray.map_x, data->ray.map_y);
			break ;
		}
		if (map[data->ray.map_y][data->ray.map_x] == '1')
			data->ray.hit = 1;
	}
}

void	ray_dist(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x == 0)
			ray->ray_dir_x = 0.0001;
		ray->wall_dist = \
		(ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		if (ray->ray_dir_y == 0)
			ray->ray_dir_y = 0.0001;
		ray->wall_dist = \
		(ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
	if (ray->wall_dist <= 0)
		ray->wall_dist = 0.1;
}

void	single_ray(t_cub3d *data, int x)
{
	t_ray	ray;

	init_ray(data, &ray, x);
	ray_vec(&data->player, &data->ray);
	dda(data, data->map.map);
	ray_dist(&data->player, &data->ray);
	render_wall(data, &data->ray, x);
}

void	raycasting(t_cub3d *data)
{
	int	x;

	x = 0;
	print_player(&data->player);
	init_player(&data->player, data);
	while (x < WIDTH_WIN)
	{
		single_ray(data, x);
		x++;
		if (x == WIDTH_WIN)
			break ;
	}
}
