/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 07:50:03 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/03 22:59:00 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void dda(t_ray *ray, int world_map[MAP_WIDTH][MAP_HEIGHT]) {
//     while (ray->hit == 0) {
//         if (ray->side_x < ray->side_y) {
//             ray->side_x += ray->delta_x;
//             ray->map_x += ray->step_x;
//             ray->side = 0;
//         } else {
//             ray->side_y += ray->delta_y;
//             ray->map_y += ray->step_y;
//             ray->side = 1;
//         }
//         if (world_map[ray->map_x][ray->map_y] > 0)
//             ray->hit = 1;
//     }
// }

// void render_wall(t_game *game, t_ray *ray, int x) {
//     int line_height = (int)(WIN_HEIGHT / ray->wall_dist);
//     int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
//     if (draw_start < 0) draw_start = 0;
//     int draw_end = line_height / 2 + WIN_HEIGHT / 2;
//     if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;
//     int color = ray->side == 1 ? 0xAAAAAA : 0xFFFFFF;

//     for (int y = draw_start; y < draw_end; y++) {
//         mlx_put_pixel(game->img, x, y, color);
//     }
// }

// void raycasting(t_game *game) {
//     for (int x = 0; x < WIN_WIDTH; x++) {
//         t_ray ray;
//         double camera_x = 2 * x / (double)WIN_WIDTH - 1;
//         ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
//         ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;
//         ray.map_x = (int)game->player.pos_x;
//         ray.map_y = (int)game->player.pos_y;
//         ray.delta_x = fabs(1 / ray.dir_x);
//         ray.delta_y = fabs(1 / ray.dir_y);
//         ray.hit = 0;

//         if (ray.dir_x < 0) {
//             ray.step_x = -1;
//             ray.side_x = (game->player.pos_x - ray.map_x) * ray.delta_x;
//         } else {
//             ray.step_x = 1;
//             ray.side_x = (ray.map_x + 1.0 - game->player.pos_x) * ray.delta_x;
//         }
//         if (ray.dir_y < 0) {
//             ray.step_y = -1;
//             ray.side_y = (game->player.pos_y - ray.map_y) * ray.delta_y;
//         } else {
//             ray.step_y = 1;
//             ray.side_y = (ray.map_y + 1.0 - game->player.pos_y) * ray.delta_y;
//         }

//         dda(&ray, game->world_map);

//         if (ray.side == 0)
//             ray.wall_dist = (ray.map_x - game->player.pos_x + (1 - ray.step_x) / 2) / ray.dir_x;
//         else
//             ray.wall_dist = (ray.map_y - game->player.pos_y + (1 - ray.step_y) / 2) / ray.dir_y;

//         render_wall(game, &ray, x);
//     }
// }

// void key_hook(mlx_key_data_t keydata, void *param) {
//     t_game *game = (t_game *)param;
//     t_player *player = &game->player;

//     if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
//         if (keydata.key == MLX_KEY_W) {
//             if (game->world_map[(int)(player->pos_x + player->dir_x * MOVE_SPEED)][(int)(player->pos_y)] == 0)
//                 player->pos_x += player->dir_x * MOVE_SPEED;
//             if (game->world_map[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == 0)
//                 player->pos_y += player->dir_y * MOVE_SPEED;
//         }
//         if (keydata.key == MLX_KEY_S) {
//             if (game->world_map[(int)(player->pos_x - player->dir_x * MOVE_SPEED)][(int)(player->pos_y)] == 0)
//                 player->pos_x -= player->dir_x * MOVE_SPEED;
//             if (game->world_map[(int)(player->pos_x)][(int)(player->pos_y - player->dir_y * MOVE_SPEED)] == 0)
//                 player->pos_y -= player->dir_y * MOVE_SPEED;
//         }
//         if (keydata.key == MLX_KEY_A) {
//             double old_dir_x = player->dir_x;
//             player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y * sin(ROT_SPEED);
//             player->dir_y = old_dir_x * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
//             double old_plane_x = player->plane_x;
//             player->plane_x = player->plane_x * cos(ROT_SPEED) - player->plane_y * sin(ROT_SPEED);
//             player->plane_y = old_plane_x * sin(ROT_SPEED) + player->plane_y * cos(ROT_SPEED);
//         }
//         if (keydata.key == MLX_KEY_D) {
//             double old_dir_x = player->dir_x;
//             player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y * sin(-ROT_SPEED);
//             player->dir_y = old_dir_x * sin(-ROT_SPEED) + player->dir_y * cos(-ROT_SPEED);
//             double old_plane_x = player->plane_x;
//             player->plane_x = player->plane_x * cos(-ROT_SPEED) - player->plane_y * sin(-ROT_SPEED);
//             player->plane_y = old_plane_x * sin(-ROT_SPEED) + player->plane_y * cos(-ROT_SPEED);
//         }
//     }
//     mlx_image_to_window(game->mlx, game->img, 0, 0);
//     raycasting(game);
// }


const int world_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
	{1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	main(void)
{
	t_game		game;
	t_player	player;

	// game.mlx = mlx_init();
	// if (!game.mlx)
	// 	return (EXIT_FAILURE);
	// game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	// if (!game.win)
	// {
	// 	free(game.mlx);
	// 	return (EXIT_FAILURE);
	// }
	player = init_player();
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!game.mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return 1;
	}
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.img)
	{
		fprintf(stderr, "Failed to create image\n");
		return 1;
	}
	game.textures[0] = mlx_load_png("path/to/texture1.png");
	game.textures[1] = mlx_load_png("path/to/texture2.png");
	game.textures[2] = mlx_load_png("path/to/texture3.png");
	game.textures[3] = mlx_load_png("path/to/texture4.png");
	if (!game.textures[0] || !game.textures[1] || !game.textures[2] || !game.textures[3])
	{
		fprintf(stderr, "Failed to load textures\n");
		return 1;
	}

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			game.world_map[i][j] = world_map[i][j];
		}
	}
	game.player = player;
	// raycasting(&game, &player);
	// mlx_loop(game.mlx);
	// mlx_destroy_window(game.mlx, game.win);
	// free(game.mlx);
	mlx_loop_hook(game.mlx, (void *)raycasting, &game);// Register the raycasting function to be called every frame
	mlx_key_hook(game.mlx, key_hook, &game);// Register the key hook for player movement
	mlx_loop(game.mlx);// Start the MLX loop
	mlx_terminate(game.mlx);// Clean up resources before exiting
	return (EXIT_SUCCESS);
}
