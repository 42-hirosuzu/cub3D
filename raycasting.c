/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:00:07 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/03 23:36:18 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_vec(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1 - player->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1 - player->pos_y) * ray->delta_y;
	}
}

void	dda(t_ray *ray, int world_map[MAP_WIDTH][MAP_HEIGHT])
{
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (world_map[ray->map_x][ray->map_y] == 1)
			ray->hit = 1;
	}
}

void	ray_dist(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void	render_wall(t_game *game, t_ray *ray, int x)
{
	int line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	// int color = (ray->side == 1) ? 0xAAAAAA : 0xFFFFFF;
	// int color;
	// if (ray->side == 1)
	//     color = 0xAAAAAA;
	// else
	// 	color = 0xFFFFFF;
	// draw_line(game, x, draw_start, draw_end, color);
	int tex_num = game->world_map[ray->map_x][ray->map_y] - 1;
	mlx_image_t *texture = game->textures[tex_num];

	// 壁のx位置の計算
	double wall_x;
	if (ray->side == 0)
		wall_x = ray->map_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = ray->map_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);

	// テクスチャのx座標
	int tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = texture->width - tex_x - 1;

	// 壁の各ピクセルのテクスチャ座標を計算しながら描画
	for (int y = draw_start; y < draw_end; y++) {
		int tex_y = (((y * 256 - WIN_HEIGHT * 128 + line_height * 128) * texture->height) / line_height) / 256;
		int color = texture->pixels[tex_y * texture->width + tex_x];
		mlx_put_pixel(game->img, x, y, color);
	}
}

// void	draw_line(t_game *game, int x, int start, int end, int color)
// {
// 	int	y;

// 	y = start;
// 	while (y < end)
// 	{
// 		mlx_pixel_put(game->mlx, game->win, x, y, color);
// 		y++;
// 	}
// }

void	print_ray(t_ray ray, t_player *player, int x)
{
	static int	i = 0;

	printf("\n%d\n", i++);
	printf("position: 2 * %d / %d - 1 = %f\n", x, WIN_WIDTH, ray.position);
	printf("dir_x: %f + %f * %f = %f\n", player->dir_x, player->plane_x, ray.position, ray.dir_x);
	printf("dir_y: %f + %f * %f = %f\n", player->dir_y, player->plane_y, ray.position, ray.dir_y);
	printf("map_x: %d\n", ray.map_x);
	printf("map_y: %d\n", ray.map_y);
	printf("side_x: %f\n", ray.side_x);
	printf("side_y: %f\n", ray.side_y);
	printf("delta_x: 1 / %f = %f\n", ray.dir_x, ray.delta_x);
	printf("delta_y: 1 / %f = %f\n", ray.dir_y, ray.delta_y);
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

void	init_ray(t_player *player, t_ray *ray, int x)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->position = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->position;
	ray->dir_y = player->dir_y + player->plane_y * ray->position;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	single_ray(t_game *game, t_player *player, int x)
{
	t_ray	ray;

	init_ray(player, &ray, x);
	// print_player(player); // debug
	// print_ray(ray, player, x); // debug
	ray_vec(player, &ray);
	dda(&ray, game->world_map);
	ray_dist(player, &ray);
	render_wall(game, &ray, x);
}

void	raycasting(t_game *game, t_player *player)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		single_ray(game, player, x);
		x++;
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
