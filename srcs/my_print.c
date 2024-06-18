/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:45:06 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/18 21:35:15 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_ray(t_ray ray, t_player *player, int x)
{
	static int	i = 0;

	ft_printf("\n%d\n", i++);
	ft_printf("ray_pos: 2 * %d / %d - 1 = %f\n", x, WIDTH_WIN, ray.ray_pos);
	ft_printf("ray_dir_x: %f + %f * %f = %f\n", player->dir_x, \
		player->plane_x, ray.ray_pos, ray.ray_dir_x);
	ft_printf("ray_dir_y: %f + %f * %f = %f\n", player->dir_y, \
		player->plane_y, ray.ray_pos, ray.ray_dir_y);
	ft_printf("map_x: %d\n", ray.map_x);
	ft_printf("map_y: %d\n", ray.map_y);
	ft_printf("side_dist_x: %f\n", ray.side_dist_x);
	ft_printf("side_dist_y: %f\n", ray.side_dist_y);
	ft_printf("delta_dist_x: 1 / %f = %f\n", ray.ray_dir_x, ray.delta_dist_x);
	ft_printf("delta_dist_y: 1 / %f = %f\n", ray.ray_dir_y, ray.delta_dist_y);
	ft_printf("wall_dist: %f\n", ray.wall_dist);
	ft_printf("step_x: %d\n", ray.step_x);
	ft_printf("step_y: %d\n", ray.step_y);
	ft_printf("hit: %d\n", ray.hit);
	ft_printf("side: %d\n", ray.side);
}

void	print_player(t_player *player)
{
	static int	i = 0;

	ft_printf("\n%d\n", i++);
	ft_printf("Player Position: (%f, %f)\n", player->pos_x, player->pos_y);
	ft_printf("Player Angle: %f\n", player->angle);
	ft_printf("Player Direction: (%f, %f)\n", player->dir_x, player->dir_y);
	ft_printf("plane_x: %f\n", player->plane_x);
	ft_printf("plane_y: %f\n", player->plane_y);
}

void	print_world_map(t_cub3d *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)map;
	while (j < data->map.height_map)
	{
		i = 0;
		while (i < data->map.width_map)
		{
			ft_printf("%d", data->map.map[j][i]);
			i++;
		}
		ft_printf("\n");
		j++;
	}
}
