/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:51:53 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/18 22:57:48 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	duplicate_player(t_cub3d *data)
{
	int	i;
	int	j;
	int	v;

	i = 0;
	v = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			{
				v++;
				if (v > 1)
				{
					printf("Please provide a player position \
						in the map (NO DUPLICATES)\n");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

int	check_player_pos(t_cub3d *data, int i, int j)
{
	if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' \
		|| data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
	{
		data->player.i = i;
		data->player.j = j;
		data->player.pos_x = j + 0.5;
		data->player.pos_y = i + 0.5;
		data->player.direction = data->map.map[i][j];
		return (0);
	}
	return (1);
}

void	get_player_pos(t_cub3d *data)
{
	int	i;
	int	j;

	i = 1;
	while (i < data->map.height_map)
	{
		j = 0;
		data->map.map[i] = ft_realloc(data->map.map[i], \
		sizeof(char) * ft_strlen(data->map.map[i]), data->map.width_map + 1);
		while (j < data->map.width_map)
		{
			if (check_player_pos(data, i, j) == 0)
				return ;
			j++;
		}
		i++;
	}
	printf("Error: Player start position not found in the map\n");
}
