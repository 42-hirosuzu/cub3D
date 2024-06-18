/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:54:04 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/18 20:48:25 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S'\
			&& *line != 'E' && *line != 'W' && *line != ' '\
			&& *line != '\t' && *line != '\n')
			return (1);
		line++;
	}
	return (0);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	check_map(t_map *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
	{
		if (is_map_line (data->map[i]) == 1)
		{
			ft_printf ("Error on line %d: Map can only be composed of \
				'01NSWE' and must not be empty.\n", (i + 1));
			exit (1);
		}
		i++;
	}
}

void	check_dimensions(t_map *data)
{
	int	i;
	int	j;
	int	highest;

	i = 0;
	highest = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
			j++;
		if (j > 100)
			exit(1);
		i++;
		if (j > highest)
			highest = j;
	}
	if (i > 100)
		exit(1);
	data->height_map = i;
	data->width_map = highest;
}
