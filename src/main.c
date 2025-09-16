/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:04 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/16 13:14:37 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_img(data->dbt, data->mlx_ptr);
	free_map(data->map);
	free_map(data->textures);
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->dbt);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

void	check_moved(int moved, t_data *data)
{
	if (moved)
		render(data);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data;
	int		moved;

	data = (t_data *)param;
	moved = 0;
	if (keycode == ESC_PRESS)
		close_window(data);
	else if (keycode == W_PRESS)
		moved = manage_w(data);
	else if (keycode == S_PRESS)
		moved = manage_s(data);
	else if (keycode == A_PRESS)
		moved = manage_a(data);
	else if (keycode == D_PRESS)
		moved = manage_d(data);
	else if (keycode == RIGHT_ARROW_PRESS)
		moved = manage_ra(data);
	else if (keycode == LEFT_ARROW_PRESS)
		moved = manage_la(data);
	else if (keycode == DOWN_ARROW_PRESS)
		moved = manage_da(data);
	else if (keycode == UP_ARROW_PRESS)
		moved = manage_ua(data);
	check_moved(moved, data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map_file>\n", 26);
		return (1);
	}
	data.view_offset = 0;
	if (check_args(&data, argv) || !data.textures)
		return (1);
	init_mlx(&data);
	if (get_texture(&data, 0, NULL) || manage_map(&data, argv))
	{
		perror("Error\nFailed to open .xpm\n");
		close_window(&data);
		return (1);
	}
	render(&data);
	mlx_hook(data.win_ptr, 17, 0, close_window, (void *)&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, (void *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
