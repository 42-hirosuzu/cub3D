/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:51:53 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/12 23:53:18 by hrinka           ###   ########.fr       */
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
						printf("Please provide a player position in the map (NO DUPLICATES)\n");
						exit(1);
					}
				}
			j++;
		}
		i++;
	}
}

void	get_player_pos(t_cub3d *data)
{
	int i = 0;
	while (i < data->map.height_map)
	{
		int j = 0;
		while (j < data->map.width_map)
		{
			printf("Checking position (%d, %d): %c\n", i, j, data->map.map[i][j]);
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' \
			|| data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			{
                data->player.i = i;
                data->player.j = j;
                data->player.pos_x = i + 0.5;
                data->player.pos_y = j + 0.5;
				data->player.direction = data->map.map[i][j];
				printf("Found player at (%d, %d)\n", i, j);
                return;
			}
            j++;
		}
		i++;
	}
	printf("Error: Player start position not found in the map\n");
}
