/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:04:35 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/27 11:43:25 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_player_position(t_data *data)
{
	int x, y;
	for (y = 0; data->map[y] != NULL; y++)
	{
		for (x = 0; data->map[y][x] != '\0'; x++)
		{
			if (data->map[y][x] == 'N')
			{
				data->dir_x = 0;
				data->dir_y = -1;
				data->plane_x = 0.66;
				data->plane_y = 0;
				data->player_x = x + 0.5;
				data->player_y = y + 0.5;
				data->map[y][x] = '0';
				return;
			}
			else if (data->map[y][x] == 'S')
			{
				data->dir_x = 0;
				data->dir_y = 1;
				data->plane_x = -0.66;
				data->plane_y = 0;
				data->player_x = x + 0.5;
				data->player_y = y + 0.5;
				data->map[y][x] = '0';
				return;
			}
			else if (data->map[y][x] == 'E')
			{
				data->dir_x = 1;
				data->dir_y = 0;
				data->plane_x = 0;
				data->plane_y = 0.66;
				data->player_x = x + 0.5;
				data->player_y = y + 0.5;
				data->map[y][x] = '0';
				return;
			}
			else if (data->map[y][x] == 'W')
			{
				data->dir_x = -1;
				data->dir_y = 0;
				data->plane_x = 0;
				data->plane_y = -0.66;
				data->player_x = x + 0.5;
				data->player_y = y + 0.5;
				data->map[y][x] = '0';
				return;
			}
		}
	}
	data->player_x = -1; // Player not found
	data->player_y = -1;
}
