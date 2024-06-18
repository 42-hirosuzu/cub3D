/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:10:39 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/18 20:48:03 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_comma(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
		{
			if (*(line + 1) == ',')
			{
				ft_printf("Invalid RGB value: consecutive commas.\n");
				exit(1);
			}
			count++;
		}
		line++;
	}
	if (count != 2)
	{
		ft_printf("Invalid RGB value: incorrect number of components.\n");
		exit(1);
	}
}

int	beflastline(char **map, int y)
{
	if (map[y + 1] != NULL && map[y + 2] != NULL)
		return (1);
	return (0);
}
