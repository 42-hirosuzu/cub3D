/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:49:22 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/05/28 00:59:17 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player(void)
{
	t_player	player;

	player.pos_x = 9.0;
	player.pos_y = 5.0;
	player.dir_x = 1.0;
	player.dir_y = 0.0;
	player.plane_x = 0.0;
	player.plane_y = 0.66;
	return (player);
}
