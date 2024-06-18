/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:08:41 by hrinka            #+#    #+#             */
/*   Updated: 2024/06/18 20:18:49 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	store_texture(t_cub3d *data, int i)
{
	const char	*textures[] = {"NO", "SO", "EA", "WE"};
	char		**paths[4];
	int			j;

	paths[1] = &data->paths.so_path;
	paths[2] = &data->paths.ea_path;
	paths[3] = &data->paths.we_path;
	paths[0] = &data->paths.no_path;
	j = 0;
	while (j < 4)
	{
		if (check_which_texture(data, i, textures[j]))
		{
			*paths[j] = remove_newline(ft_strnstr(data->file_content[i],
						"textures", ft_strlen(data->file_content[i])));
			return ;
		}
		j++;
	}	
	if (ft_strchr(data->file_content[i], 'F'))
		data->textures.floor_hex
			= rgb_to_hex(skip_to_rgb_values(data->file_content[i]));
	else if (ft_strchr(data->file_content[i], 'C'))
		data->textures.sky_hex
			= rgb_to_hex(skip_to_rgb_values(data->file_content[i]));
}

int	store_textures_path(t_cub3d *data, int length)
{
	int	i;

	i = 0;
	while (data->file_content[i] != NULL && i < length)
	{
		store_texture(data, i);
		i++;
	}
	if (check_path_rgb(data) != 0)
	{
		ft_printf("Error: Texture path validation failed.\n");
		return (0);
	}
	return (0);
}

int	map_length(t_cub3d *data, int index)
{
	int	i;

	i = 0;
	while (data->file_content[index] != NULL)
	{
		i++;
		index++;
	}
	return (i);
}

void	copy_map_content(t_cub3d *data, int index)
{
	int		i;
	char	*line;

	i = 0;
	while (data->file_content[index] != NULL)
	{
		line = data->file_content[index];
		ft_printf("Copying line: %s\n", line);
		data->map.map[i] = ft_strdup(data->file_content[index]);
		data->map.tmp[i] = ft_strdup(data->file_content[index]);
		i++;
		index++;
	}
	data->map.map[i] = NULL;
	data->map.tmp[i] = NULL;
}

int	store_map(t_cub3d *data, int index)
{
	int	map_length_val;

	while (data->file_content[index] != NULL
		&& empty_line(data->file_content[index]) == 0)
		index++;
	map_length_val = map_length(data, index);
	data->map.map = malloc((map_length_val + 1) * sizeof(char *));
	data->map.tmp = malloc((map_length_val + 1) * sizeof(char *));
	if (!data->map.map || !data->map.tmp)
	{
		ft_printf("Error: Unable to allocate memory for map\n");
		exit(EXIT_FAILURE);
	}
	copy_map_content(data, index);
	ft_printf("Map copied successfully with len %d\n", map_length_val);
	return (0);
}
