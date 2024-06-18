/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:45:58 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/18 19:46:27 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_player *player, t_cub3d *data)
{
	float	angle;

	angle = to_rad(player->angle);
	player->dir_x = cos((angle));
	player->dir_y = sin((angle));
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	data->player = *player;
}

void	init_ray(t_cub3d *data, t_ray *ray, int x)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->ray_pos = 2 * x / (double)WIDTH_WIN - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->ray_pos;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->ray_pos;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	data->ray = *ray;
}

float	to_rad(float degree)
{
	return (degree * (M_PI / 180));
}
