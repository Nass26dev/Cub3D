/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keypress.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:56:23 by nass              #+#    #+#             */
/*   Updated: 2025/09/12 14:10:56 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	manage_w(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x + data->dir_x * MOVE_SPEED;
	new_y = data->player_y + data->dir_y * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
		data->player_x = new_x;
	if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
		data->player_y = new_y;
	return (true);
}

bool	manage_s(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x - data->dir_x * MOVE_SPEED;
	new_y = data->player_y - data->dir_y * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
		data->player_x = new_x;
	if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
		data->player_y = new_y;
	return (true);
}

bool	manage_a(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x - data->plane_x * MOVE_SPEED;
	new_y = data->player_y - data->plane_y * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
		data->player_x = new_x;
	if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
		data->player_y = new_y;
	return (true);
}

bool	manage_d(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x + data->plane_x * MOVE_SPEED;
	new_y = data->player_y + data->plane_y * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
		data->player_x = new_x;
	if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
		data->player_y = new_y;
	return (true);
}
