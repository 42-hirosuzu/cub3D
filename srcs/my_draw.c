/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 02:04:16 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/06/18 22:22:40 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_wall_tex(t_draw *draw, t_cub3d *data)
{
	if (data->ray.side == 0)
		draw->wall_x = data->player.pos_y + \
			data->ray.wall_dist * data->ray.ray_dir_y;
	else
		draw->wall_x = data->player.pos_x + \
			data->ray.wall_dist * data->ray.ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	if (data->ray.side == 0)
	{
		if (data->ray.ray_dir_x > 0)
			draw->texture_img = data->textures.we_texture;
		else
			draw->texture_img = data->textures.ea_texture;
	}
	else
	{
		if (data->ray.ray_dir_y > 0)
			draw->texture_img = data->textures.so_texture;
		else
			draw->texture_img = data->textures.no_texture;
	}
}

void	init_draw(t_draw *draw, t_cub3d *data)
{
	ft_memset(draw, 0, sizeof(t_draw));
	draw->line_height = (int)(HEIGHT_WIN / data->ray.wall_dist);
	draw->draw_start = -draw->line_height / 2 + HEIGHT_WIN / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HEIGHT_WIN / 2;
	if (draw->draw_end >= HEIGHT_WIN)
		draw->draw_end = HEIGHT_WIN - 1;
	set_wall_tex(draw, data);
	if (!draw->texture_img)
	{
		ft_printf("Failed to get texture image\n");
		exit(EXIT_FAILURE);
	}
}

void	render_pixel(t_cub3d *data, t_draw draw, int tex_x, int x, int y)
{
	int			d;
	int			tex_y;
	uint32_t	color;

	d = y * 256 - HEIGHT_WIN * 128 + draw.line_height * 128;
	tex_y = ((d * draw.texture_img->height) / draw.line_height) / 256;
	color = get_texel_image(draw.texture_img, tex_x, tex_y);
	mlx_put_pixel(data->map.img, x, y, color);
}

void	render_wall(t_cub3d *data, t_ray *ray, int x)
{
	t_draw		draw;
	int			tex_x;
	int			y;

	init_draw(&draw, data);
	if (!draw.texture_img)
	{
		ft_printf("Failed to get texture image\n");
		return ;
	}
	tex_x = (int)(draw.wall_x * (double)(draw.texture_img->width));
	if ((ray->side == 0 && ray->ray_dir_x < 0) \
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = draw.texture_img->width - tex_x - 1;
	y = draw.draw_start;
	while (y < draw.draw_end)
	{
		render_pixel(data, draw, tex_x, x, y);
		y++;
	}
}

uint32_t	get_texel_image(mlx_image_t *image, uint32_t tex_x, uint32_t tex_y)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	index = (tex_y * image->width + tex_x) * 4;
	r = image->pixels[index];
	g = image->pixels[index + 1];
	b = image->pixels[index + 2];
	a = image->pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
