/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_keypress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:03:55 by nass              #+#    #+#             */
/*   Updated: 2025/09/12 15:02:52 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	manage_ra(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
	data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y
		* sin(-ROT_SPEED);
	data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y
		* cos(-ROT_SPEED);
	return (true);
}

bool	manage_la(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
	data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y
		* sin(ROT_SPEED);
	data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y;
	return (true);
}

bool	manage_da(t_data *data)
{
	data->view_offset -= 50;
	if (data->view_offset < -200)
		data->view_offset = -200;
	return (true);
}

bool	manage_ua(t_data *data)
{
	data->view_offset += 50;
	if (data->view_offset > 200)
		data->view_offset = 200;
	return (true);
}
