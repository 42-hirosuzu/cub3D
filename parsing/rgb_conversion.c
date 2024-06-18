/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:24:22 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/18 20:18:48 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*skip_to_rgb_values(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 'F' && line[i] != 'C' && line[i] != ' '
			&& line[i] != '\t')
			return (&line[i]);
		i++;
	}
	return (NULL);
}

void	validate_rgb_values(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '\0')
		{
			ft_printf("Please fix the RGB values, empty string found.\n");
			exit(1);
		}
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]) && str[i][j] != '\n')
			{
				ft_printf("Please fix RGB values, invalid: %s\n", &str[i][j]);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	nb_rgb_elem(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

// long	return_hex_rgb(char *line)
// {
// 	char	**values;
// 	long	hex_val;
// 	int		r;
// 	int		g;
// 	int		b;

// 	values = ft_split(line, ',');
// 	if (nb_rgb_elem(values) != 3)
// 	{
// 		ft_printf("Error: Invalid number of RGB values\n");
// 		free_2dchar_array(values);
// 		exit(1);
// 	}
// 	validate_rgb_values(values);
// 	if (values && values[0] && values[1] && values[2])
// 	{
// 		r = ft_atoi(values[0]);
// 		g = ft_atoi(values[1]);
// 		b = ft_atoi(values[2]);
// 		free_2dchar_array(values);
// 		if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0
// 				&& b <= 255))
// 		{
// 			hex_val = ((long)r << 24) | ((long)g << 16) | (long)b << 8 | (1
// 					* 255);
// 			return (hex_val);
// 		}
// 	}
// 	return (-1);
// }

long	return_hex_rgb(char *line)
{
	char	**values;
	long	hex_val;
	int		r;
	int		g;
	int		b;

	values = ft_split(line, ',');
	if (nb_rgb_elem(values) > 3)
		exit(1);
	validate_rgb_values(values);
	if (values && values[0] && values[1] && values[2])
	{
		r = ft_atoi(values[0]);
		g = ft_atoi(values[1]);
		b = ft_atoi(values[2]);
		free_2dchar_array(values);
		if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0
				&& b <= 255))
		{
			hex_val = ((long)r << 24) | ((long)g << 16) | (long)b << 8 | (1
					* 255);
			return (hex_val);
		}
	}
	return (-1);
}

long	rgb_to_hex(char *line)
{
	check_comma(line);
	return (return_hex_rgb(line));
}
