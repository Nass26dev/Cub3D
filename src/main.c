/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:04 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/29 13:35:51 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		close_window(data);
	return (0);
}

void render(t_data *data)
{
	(void)data;
}

t_point get_point(int fd)
{
	char *line;
	t_point point;
	
	point.x = 0;
	point.y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (point.y == 0)
			point.x = ft_strlen(line);
		if (line == NULL)
			break;
		free(line);
		point.y++;
	}
	return (point);
}

char **get_map(int fd, t_point point)
{
	char **map;
	char *line;
	int i;

	map = malloc(sizeof(char *) * (point.y + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < point.y)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	return (map);
}

char **parse_file(const char *filename)
{
	int fd;
	t_point point;
	char **map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	// check_error(fd);
	point = get_point(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	map = get_map(fd, point);
	return (map);
}

int main(int argc, char **argv)
{
	t_data data;
	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map_file>\n", 26);
		return (1);
	}
	data.map = parse_file(argv[1]);
	data.mlx_ptr = mlx_init();
	mlx_get_screen_size(data.mlx_ptr, &data.width, &data.height);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Cub3D");
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bpp, &data.ll, &data.endian);
	render(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_window, (void *)&data);
	mlx_key_hook(data.win_ptr, key_hook, (void *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
