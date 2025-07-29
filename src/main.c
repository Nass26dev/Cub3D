/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:04 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/29 17:06:22 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void free_map(char **map)
{
	int i;

	if (!map)
		return;
	for (i = 0; map[i]; i++)
		free(map[i]);
	free(map);
}

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
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		close_window(data);
	return (0);
}

void render(t_data *data)
{
    int x, y;
    unsigned int white_color = 0x00FFFFFF;

    for (y = 0; y < data->height; y++)
    {
        for (x = 0; x < data->width; x++)
        {
            char *dst = data->addr + (y * data->ll + x * (data->bpp / 8));
            *(unsigned int *)dst = white_color;
        }
    }
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

char **parse_file(const char *filename, t_data *data)
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
	data->map_height = point.y;
	data->map_width = point.x;
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

void print_minimap(t_data *data)
{
    int size;
    int offset_x;
    int offset_y;
    int x, y;
    unsigned int color = 0x000000; // Couleur noir (assuré en hex)

    size = data->width * 13 / 100;

    // Définir un décalage du bord supérieur gauche (par exemple 5% largeur et hauteur)
    offset_x = data->width * 3 / 100;  // 5% du bord gauche
    offset_y = data->height * 5 / 100; // 5% du bord haut

    for (y = 0; y < size; y++)
    {
        for (x = 0; x < size; x++)
        {
            int px = offset_x + x;
            int py = offset_y + y;

            if (px >= 0 && px < data->width && py >= 0 && py < data->height)
            {
                char *dst = data->addr + (py * data->ll + px * (data->bpp / 8));
                *(unsigned int *)dst = color;
            }
        }
    }
}

void get_player_position(char **map, int *player_x, int *player_y)
{
	int x, y;

	for (y = 0; map[y] != NULL; y++)
	{
		for (x = 0; map[y][x] != '\0'; x++)
		{
			if (map[y][x] == 'N')
			{
				*player_x = x;
				*player_y = y;
				return;
			}
			else if (map[y][x] == 'S')
			{
				*player_x = x;
				*player_y = y;
				return;
			}
			else if (map[y][x] == 'E')
			{
				*player_x = x;
				*player_y = y;
				return;
			}
			else if (map[y][x] == 'W')
			{
				*player_x = x;
				*player_y = y;
				return;
			}
		}
	}
	*player_x = -1; // Player not found
	*player_y = -1;
}

int main(int argc, char **argv)
{
	t_data data;
	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map_file>\n", 26);
		return (1);
	}
	data.fov = 60.0; // Example FOV value
	data.player_angle = 0;
	data.map = parse_file(argv[1], &data);
	get_player_position(data.map, &data.player_x, &data.player_y);
	data.mlx_ptr = mlx_init();
	mlx_get_screen_size(data.mlx_ptr, &data.width, &data.height);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Cub3D");
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bpp, &data.ll, &data.endian);
	render(&data);
	print_minimap(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_window, (void *)&data);
	mlx_key_hook(data.win_ptr, key_hook, (void *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
