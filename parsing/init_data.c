/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:32:34 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/18 21:48:55 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_struct(t_cub3d *data)
{
	data->file_content = NULL;
	data->paths.no_path = NULL;
	data->paths.so_path = NULL;
	data->paths.we_path = NULL;
	data->paths.ea_path = NULL;
	data->map.map = NULL;
	data->textures.sky_hex = -1;
	data->textures.floor_hex = -1;
	data->player.direction = 0;
}

void	check_walls(t_map *data)
{
	int	i;
	int	j;

	i = 1;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
		{
			if ((!data->map[i + 1] || data->map[i][j + 1] == '\n' || i == 0 \
			|| j == 0) && (data->map[i][j] != '1' && data->map[i][j] != ' '))
			{
				ft_printf("Error: Map boundaries must be walls or empty.\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	check_path_rgb(t_cub3d *data)
{
	if (data->paths.no_path == NULL)
		return (1);
	if (data->paths.so_path == NULL)
		return (1);
	if (data->paths.we_path == NULL)
		return (1);
	if (data->paths.ea_path == NULL)
		return (1);
	if (data->textures.floor_hex == -1)
		return (1);
	if (data->textures.sky_hex == -1)
		return (1);
	return (0);
}

void	init_game(char *path_file, t_cub3d *data)
{
	init_struct(data);
	if (check_extension(path_file, ".cub") == 1)
	{
		ft_printf("Please enter a map folder with (\".cub\")");
		exit(1);
	}
	get_file_content(path_file, data);
	parse_file_content(data);
	sleep(1);
	duplicate_player(data);
	check_dimensions(&data->map);
	get_player_pos(data);
	check_walls(&data->map);
	check_valid_path(data, data->player.i, data->player.j);
}

void	init_textures(mlx_t *mlx, t_cub3d *data)
{
	const char		*paths[4] = {data->paths.no_path, data->paths.so_path,
		data->paths.ea_path, data->paths.we_path};
	mlx_image_t		**images[4];
	mlx_texture_t	*loaded_texture;
	int				i;

	images[0] = &data->textures.no_texture;
	images[1] = &data->textures.so_texture;
	images[2] = &data->textures.ea_texture;
	images[3] = &data->textures.we_texture;
	i = 0;
	while (i < 4)
	{
		loaded_texture = mlx_load_png(paths[i]);
		if (!loaded_texture)
		{
			ft_printf("Error: Couldn't initialize texture: %s\n", paths[i]);
			exit(1);
		}
		*images[i] = mlx_texture_to_image(mlx, loaded_texture);
		mlx_delete_texture(loaded_texture);
		i++;
	}
}
