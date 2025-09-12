/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:04:35 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/12 15:34:33 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	manage_n(t_data *data, int x, int y)
{
	data->dir_x = 0;
	data->dir_y = -1;
	data->plane_x = 0.66;
	data->plane_y = 0;
	data->player_x = x + 0.5;
	data->player_y = y + 0.5;
	data->map[y][x] = '0';
}

void	manage_s(t_data *data, int x, int y)
{
	data->dir_x = 0;
	data->dir_y = 1;
	data->plane_x = -0.66;
	data->plane_y = 0;
	data->player_x = x + 0.5;
	data->player_y = y + 0.5;
	data->map[y][x] = '0';
}

void	manage_e(t_data *data, int x, int y)
{
	data->dir_x = 1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
	data->player_x = x + 0.5;
	data->player_y = y + 0.5;
	data->map[y][x] = '0';
}

void	manage_w(t_data *data, int x, int y)
{
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = -0.66;
	data->player_x = x + 0.5;
	data->player_y = y + 0.5;
	data->map[y][x] = '0';
}

void	get_player_position(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y] != NULL)
	{
		x = -1;
		while (data->map[y][++x] != '\0')
		{
			if (data->map[y][x] == 'N')
				return (manage_n(data, x, y));
			else if (data->map[y][x] == 'S')
				return (manage_s(data, x, y));
			else if (data->map[y][x] == 'E')
				return (manage_e(data, x, y));
			else if (data->map[y][x] == 'W')
				return (manage_w(data, x, y));
		}
		y++;
	}
	data->player_x = -1;
	data->player_y = -1;
}
