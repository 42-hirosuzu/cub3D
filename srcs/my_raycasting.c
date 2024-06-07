/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:00:07 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/08 01:22:48 by hrinka           ###   ########.fr       */
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


void	dda(t_cub3d *data, int **world_map)
{
	printf("dda\n");
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
		// if (data->ray.map_x < 0 || data->ray.map_x >= data->map.width_map || data->ray.map_y < 0 || data->ray.map_y >= data->map.height_map) {
        //     printf("Out of map bounds: map_x=%d, map_y=%d\n", data->ray.map_x, data->ray.map_y);
        //     break;  // Break the loop if out of bounds
        // }
		if (world_map[data->ray.map_x][data->ray.map_y] > 0)
		{
			printf("hit\n");
			data->ray.hit = 1;
			return ;
		}
		printf("Checking hit: map_x=%d, map_y=%d, hit=%d\n", data->ray.map_x, data->ray.map_y, data->ray.hit);
		printf("data->ray.side_dist_x: %f , data->ray.side_dist_y: %f\n", data->ray.side_dist_x, data->ray.side_dist_y);
		printf("data->ray.step_x: %d , data->ray.step_y: %d\n", data->ray.step_x, data->ray.step_y);
		printf("world_map[data->ray.map_x][data->ray.map_y]: %d\n", world_map[data->ray.map_x][data->ray.map_y]);
	}
}

// void	ray_dist(t_player *player, t_ray *ray)
// {
// 	if (ray->side == 0)
// 		ray->wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
// 	else
// 		ray->wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
// 	printf("ray->wall_dist: %f\n", ray->wall_dist);
// }

void ray_dist(t_player *player, t_ray *ray) {
    if (ray->side == 0) {
        //  if (ray->ray_dir_x == 0) ray->ray_dir_x = 0.0001;  // 非常に小さい値を0とみなさないようにする
        ray->wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    } else {
        // if (    sray->ray_dir_y == 0) ray->ray_dir_y = 0.0001;  // 非常に小さい値を0とみなさないようにする
        ray->wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
    }
    // printf("ray->wall_dist: %f\n", ray->wall_dist);
    // if (ray->wall_dist <= 0) {
    //     ray->wall_dist = 0.1;  // 最小値を設定して無限ループや他の数値エラーを防ぐ
    // }
}

void	render_wall(t_cub3d *data, t_ray *ray, int x)
{
	int line_height = (int)(HEIGHT_WIN / ray->wall_dist);
	int draw_start = -line_height / 2 + HEIGHT_WIN / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + HEIGHT_WIN / 2;
	if (draw_end >= HEIGHT_WIN)
		draw_end = HEIGHT_WIN - 1;
	int color;
	if (ray->side == 1)
	    color = 0xAAAAAA;
	else
    	color = 0xFFFFFF;
	draw_line(data, x, draw_start, draw_end, color);
}

void	draw_line(t_cub3d *data, int x, int start, int end, int color)
{
	int	y;

	y = start;
	// printf("start: %d\n", start);
	// printf("end: %d\n", end);
	while (y < end)
	{
		mlx_put_pixel(data->map.img, x, y, color);
		y++;
	}
}

void	print_ray(t_ray ray, t_player *player, int x)
{
	static int	i = 0;

	printf("\n%d\n", i++);
    printf("ray_pos: 2 * %d / %d - 1 = %f\n", x, WIDTH_WIN, ray.ray_pos);
    printf("ray_dir_x: %f + %f * %f = %f\n", player->dir_x, player->plane_x, ray.ray_pos, ray.ray_dir_x);
    printf("ray_dir_y: %f + %f * %f = %f\n", player->dir_y, player->plane_y, ray.ray_pos, ray.ray_dir_y);
    printf("map_x: %d\n", ray.map_x);
    printf("map_y: %d\n", ray.map_y);
    printf("side_dist_x: %f\n", ray.side_dist_x);
    printf("side_dist_y: %f\n", ray.side_dist_y);
    printf("delta_dist_x: 1 / %f = %f\n", ray.ray_dir_x, ray.delta_dist_x);
    printf("delta_dist_y: 1 / %f = %f\n", ray.ray_dir_y, ray.delta_dist_y);
    printf("wall_dist: %f\n", ray.wall_dist);
    printf("step_x: %d\n", ray.step_x);
    printf("step_y: %d\n", ray.step_y);
    printf("hit: %d\n", ray.hit);
    printf("side: %d\n", ray.side);
}

void	print_player(t_player *player)
{
	static int	i = 0;

	printf("\n%d\n", i++);
	printf("pos_x: %f\n", player->pos_x);
	printf("pos_y: %f\n", player->pos_y);
	printf("dir_x: %f\n", player->dir_x);
	printf("dir_y: %f\n", player->dir_y);
	printf("plane_x: %f\n", player->plane_x);
	printf("plane_y: %f\n", player->plane_y);
}

void	init_player(t_player *player, t_cub3d *data)
{
	// printf("init_player\n");
	player->pos_x = player->i;
	// printf("data->map.px: %f\n", data->map.px);
	// printf("player->pos_x: %f\n", player->pos_x);
	player->pos_y = player->j;
	player->dir_x = cos(player->angle) - sin(player->angle);
	player->dir_y = sin(player->angle) + cos(player->angle);
	player->plane_x = 0;
	player->plane_y = 0.66;
	data->player = *player;
}

void init_ray(t_cub3d *data, t_ray *ray, int x) {
    ft_memset(ray, 0, sizeof(t_ray));
    ray->ray_pos = 2 * x / (double)WIDTH_WIN - 1;
    ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->ray_pos;
    ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->ray_pos;
    ray->map_x = (int)data->player.pos_x;
    ray->map_y = (int)data->player.pos_y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
	ray_vec(&data->player, ray);
    // printf("init_ray\n");
    // printf("player->pos_x: %f\n", player->pos_x);
    // printf("ray->map_x: %d\n", ray->map_x);
    // printf("ray->ray_dir_x: %f\n", ray->ray_dir_x);
    // printf("ray->ray_dir_y: %f\n", ray->ray_dir_y);
	data->ray = *ray;
}


void	single_ray(t_cub3d *data, int x)
{
	t_ray	ray;

	init_ray(data, &ray, x);
	// print_player(player); // debug
	// print_ray(ray, &data->player, x); // debug
	// ray_vec(&data->player, &ray);
	print_ray(ray, &data->player, x); // debug
	dda(data, data->map.world_map);
	ray_dist(&data->player, &ray);
	render_wall(data, &ray, x);
}

void	print_world_map(t_cub3d *data, int **world_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)world_map;
	while (j < data->map.height_map)
	{
		i = 0;
		while (i < data->map.width_map)
		{
			printf("%d", data->map.world_map[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void	raycasting(t_cub3d *data)
{
	int	x;

	x = 0;
	printf("raycasting\n");
	print_world_map(data, data->map.world_map);
	init_player(&data->player, data);
	while (x < WIDTH_WIN)
	{
		// printf("x: %d\n", x);
		single_ray(data, x);
		x++;
		if (x == WIDTH_WIN) {
			// printf("end\n");
			break;
		}
	}
}
