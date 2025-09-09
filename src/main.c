/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:04 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/09 10:51:36 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_map(data->map);
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data = (t_data *)param;
	int		moved = 0;
	//windows --> 122 / 115 / 113 / 100
	//linux -- >  119 / 115 / 97  / 100
	if (keycode == 65307)
		close_window(data);
		else if (keycode == 119) // W
	{
		double new_x = data->player_x + data->dir_x * MOVE_SPEED;
		double new_y = data->player_y + data->dir_y * MOVE_SPEED;

		if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
			data->player_x = new_x;
		if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
			data->player_y = new_y;
		moved = 1;
	}
	else if (keycode == 115) // S
	{
		double new_x = data->player_x - data->dir_x * MOVE_SPEED;
		double new_y = data->player_y - data->dir_y * MOVE_SPEED;

		if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
			data->player_x = new_x;
		if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
			data->player_y = new_y;
		moved = 1;
	}
	else if (keycode == 97) // A (Strafe gauche)
	{
		double new_x = data->player_x - data->plane_x * MOVE_SPEED;
		double new_y = data->player_y - data->plane_y * MOVE_SPEED;

		if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
			data->player_x = new_x;
		if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
			data->player_y = new_y;
		moved = 1;
	}
	else if (keycode == 100) // D (Strafe droite)
	{
		double new_x = data->player_x + data->plane_x * MOVE_SPEED;
		double new_y = data->player_y + data->plane_y * MOVE_SPEED;

		if (data->map[(int)(data->player_y)][(int)(new_x)] != '1')
			data->player_x = new_x;
		if (data->map[(int)(new_y)][(int)(data->player_x)] != '1')
			data->player_y = new_y;
		moved = 1;
	}
	else if (keycode == 65361) // fleche gauche
	{
		double old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
		data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);
		double old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y * sin(-ROT_SPEED);
		data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y * cos(-ROT_SPEED);
		moved = 1;
	}
	else if (keycode == 65363) // fleche droite
	{
		double old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
		data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);
		double old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y * sin(ROT_SPEED);
		data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y * cos(ROT_SPEED);
		moved = 1;
	}
	else if (keycode == 65364) // flèche bas
	{
		data->view_offset -= 50; // vers le haut (regarde plus haut)
		if (data->view_offset <  -200)
			data->view_offset = -200;
		moved = 1;
	}
	else if (keycode == 65362) // flèche haut
	{
		data->view_offset += 50; // vers le bas (regarde plus bas)
		if (data->view_offset > 200)
			data->view_offset = 200;
		moved = 1;
	}
	if (moved)
		render(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_data 	data;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map_file>\n", 26);
		return (1);
	}
	data.view_offset = 0;
	data.map = parse_file(argv[1], &data);
	data.textures = fetch_textures_file(argv[1]);
	get_player_position(&data);
	data.mlx_ptr = mlx_init();
	data.width = 800;
	data.height = 600;
	// mlx_get_screen_size(data.mlx_ptr, &data.width, &data.height);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Cub3D");
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bpp, &data.ll, &data.endian);
	get_texture(&data);
	render(&data);
	mlx_hook(data.win_ptr, 17, 0, close_window, (void *)&data);
	// mlx_hook(data.win_ptr, 2, 1L << 0, key_hook, (void *)&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, (void *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
