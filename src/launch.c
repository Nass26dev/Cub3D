/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:52:36 by nass              #+#    #+#             */
/*   Updated: 2025/09/16 13:20:17 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_args(t_data *data, char **argv)
{
	data->textures = fetch_textures_file(argv[1], 0, 0);
	if (!data->textures)
		return (1);
	if (is_ceiling_color(data->textures) || is_floor_color(data->textures)
		|| is_text_paths(data->textures))
	{
		data->error_msg = ft_strdup("Missing argument(s)");
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(data->error_msg, 2);
		free(data->textures);
		return (1);
	}
	return (0);
}

bool	manage_map(t_data *data, char **argv)
{
	data->map = parse_file(argv[1], data);
	if (!data->map)
		return (1);
	if (parse_error(data))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(data->error_msg, 2);
		error_parse_cleanup(data);
		return (1);
	}
	get_player_position(data);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->height = 720;
	data->width = 1280;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"Cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->ll,
			&data->endian);
}
