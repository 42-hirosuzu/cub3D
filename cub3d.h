/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 07:51:35 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/03 21:45:40 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
// # include <ctype.h>
// # include <string.h>
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "./Libft/libft.h"
# include "./Libft/get_next_line.h"
# include "./Libft/printf.h"
// # include "./minilibx-linux/mlx.h"
# include "MLX42/MLX42.h"

# define WIN_WIDTH	640
# define WIN_HEIGHT	480
# define MAP_WIDTH	24
# define MAP_HEIGHT	24

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_ray
{
	int			map_x;
	int			map_y;
	double		position;
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	double		wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_ray;

// typedef struct s_game
// {
// 	void	*mlx;
// 	void	*win;
// 	int		world_map[MAP_WIDTH][MAP_HEIGHT];
// }				t_game;
typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*textures[4];
	mlx_t 		*win;
	int			world_map[MAP_WIDTH][MAP_HEIGHT];
	t_player	player;
}				t_game;


void		draw_line(t_game *game, int x, int start, int end, int color);
void		ray_vec(t_player *player, t_ray *ray);
void		dda(t_ray *ray, int world_map[MAP_WIDTH][MAP_HEIGHT]);
void		ray_dist(t_player *player, t_ray *ray);
void		render_wall(t_game *game, t_ray *ray, int x);
void		single_ray(t_game *game, t_player *player, int x);
void		raycasting(t_game *game, t_player *player);
t_player	init_player(void);
void		key_hook(mlx_key_data_t keydata, void *param);

#endif