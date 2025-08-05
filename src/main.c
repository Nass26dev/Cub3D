/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:04 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/05 14:49:52 by nyousfi          ###   ########.fr       */
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

void init_dda(t_data *data, t_dda *dda, t_raycast *rc)
{
	if (rc->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (data->player_x - rc->map_x) * rc->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (rc->map_x + 1.0 - data->player_x) * rc->delta_x;
	}
	if (rc->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (data->player_y - rc->map_y) * rc->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (rc->map_y + 1.0 - data->player_y) * rc->delta_y;
	}
	dda->hit = 0;
}

void print_line(t_data *data, t_dda *dda, int x)
{
	int line_height;
	int draw_start;
	int draw_end;
	
	line_height = (int)(data->height / dda->wall_dist);
	draw_start = -line_height / 2 + data->height / 2;
	if (draw_start < 0)
	draw_start = 0;
	draw_end = line_height / 2 + data->height / 2;
	if (draw_end >= data->height)
	draw_end = data->height - 1;
	
	// Set color based on side
	unsigned int color = (dda->side == 1) ? 0x00FF00 : 0xFF0000; // Green for Y side, Red for X side
	
	for (int y = draw_start; y < draw_end; y++)
	{
		char *dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void dda(t_data *data, t_raycast *rc, int x)
{
	t_dda dda;
	
	init_dda(data, &dda, rc);
	while (dda.hit == 0)
	{
		if (dda.side_dist_x < dda.side_dist_y)
		{
			dda.side_dist_x += rc->delta_x;
			rc->map_x += dda.step_x;
			dda.side = 0;
		}
		else
		{
			dda.side_dist_y += rc->delta_y;
			rc->map_y += dda.step_y;
			dda.side = 1;
		}
		if (data->map[rc->map_y][rc->map_x] == '1')
		dda.hit = 1;
	}
	if (dda.side == 0)
	dda.wall_dist = (rc->map_x - data->player_x + (1 - dda.step_x) / 2) / rc->ray_dir_x;
	else
	dda.wall_dist = (rc->map_y - data->player_y + (1 - dda.step_y) / 2) / rc->ray_dir_y;
	print_line(data, &dda , x);			
}

void raycast(t_data *data)
{
	int x;
	t_raycast rc;
	x = 0;
	while (x < data->width)
	{
		rc.camera_x = 2 * x / (double)data->width - 1;
		rc.ray_dir_x = data->dir_x + data->plane_x * rc.camera_x;
		rc.ray_dir_y = data->dir_y + data->plane_y * rc.camera_x;
		rc.map_x = (int)data->player_x;
		rc.map_y = (int)data->player_y;
		rc.delta_x = fabs(1 / rc.ray_dir_x);
		rc.delta_y = fabs(1 / rc.ray_dir_y);
		dda(data, &rc, x);
		x++;
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
		if (line == NULL)
			break;
		if (point.y == 0)
			point.x = ft_strlen(line) - 1;
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

#define MINIMAP_SCALE 20  // Plus grand = plus petit affichage (1 = full scale, 4 = 1/4 taille réelle)

void draw_pixel(t_data *data, int x, int y, unsigned int color)
{
    if (x >= 0 && x < data->width && y >= 0 && y < data->height)
    {
        char *dst = data->addr + (y * data->ll + x * (data->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_square(t_data *data, int x, int y, int size, unsigned int color)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            draw_pixel(data, x + j, y + i, color);
        }
    }
}

void print_minimap(t_data *data)
{
    int offset_x = data->width * 3 / 100;
    int offset_y = data->height * 5 / 100;

    int tile_size = MINIMAP_SCALE; // taille de chaque case en px dans la minimap

    for (int y = 0; y < data->map_height; y++)
    {
        for (int x = 0; x < data->map_width; x++)
        {
            char tile = data->map[y][x];
            unsigned int color;

            if (tile == '1') // mur
                color = 0x777777; // gris
            else
                color = 0xFFFFFF; // sol/vide

            int draw_x = offset_x + x * tile_size;
            int draw_y = offset_y + y * tile_size;
            draw_square(data, draw_x, draw_y, tile_size, color);
        }
    }
    // Dessiner le joueur en rouge
    int player_draw_x = offset_x + data->player_x * tile_size;
    int player_draw_y = offset_y + data->player_y * tile_size;
    draw_square(data, player_draw_x, player_draw_y, tile_size, 0xFF0000); // rouge
}
void render(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->ll, &data->endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	print_minimap(data);
}

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
				data->player_x = x;
				data->player_y = y;
				data->map[y][x] = '0';
				return;
			}
			else if (data->map[y][x] == 'S')
			{
				data->dir_x = 0;
				data->dir_y = 1;
				data->plane_x = -0.66;
				data->plane_y = 0;
				data->player_x = x;
				data->player_y = y;
				data->map[y][x] = '0';
				return;
			}
			else if (data->map[y][x] == 'E')
			{
				data->dir_x = 1;
				data->dir_y = 0;
				data->plane_x = 0;
				data->plane_y = 0.66;
				data->player_x = x;
				data->player_y = y;
				data->map[y][x] = '0';
				return;
			}
			else if (data->map[y][x] == 'W')
			{
				data->dir_x = -1;
				data->dir_y = 0;
				data->plane_x = 0;
				data->plane_y = -0.66;
				data->player_x = x;
				data->player_y = y;
				data->map[y][x] = '0';
				return;
			}
		}
	}
	data->player_x = -1; // Player not found
	data->player_y = -1;
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 119) // W
		data->move_forward = 1;
	else if (keycode == 115) // S
		data->move_backward = 1;
	else if (keycode == 97) // A
		data->strafe_left = 1;
	else if (keycode == 100) // D
		data->strafe_right = 1;
	else if (keycode == 65361) // fleche gauche
		data->rotate_left = 1;
	else if (keycode == 65363) // fleche droite
		data->rotate_right = 1;
	else if (keycode == 65307) // ESC
		exit(0);
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->move_forward = 0;
	else if (keycode == 115)
		data->move_backward = 0;
	else if (keycode == 97)
		data->strafe_left = 0;
	else if (keycode == 100)
		data->strafe_right = 0;
	else if (keycode == 65361)
		data->rotate_left = 0;
	else if (keycode == 65363)
		data->rotate_right = 0;
	return (0);
}

int update_loop(t_data *data)
{
	if (data->move_forward)
		move_forward(data);
	if (data->move_backward)
		move_backward(data);
	if (data->strafe_left)
		strafe_left(data);
	if (data->strafe_right)
		strafe_right(data);
	if (data->rotate_left)
		rotate_left(data);
	if (data->rotate_right)
		rotate_right(data);
	render(data);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data = (t_data *)param;
	int		moved = 0;

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
	if (moved)
		render(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;
	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map_file>\n", 26);
		return (1);
	}
	data.map = parse_file(argv[1], &data);
	get_player_position(&data);
	data.mlx_ptr = mlx_init();
	mlx_get_screen_size(data.mlx_ptr, &data.width, &data.height);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Cub3D");
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bpp, &data.ll, &data.endian);
	render(&data);
	mlx_loop_hook(data.mlx_ptr, update_loop, &data);
	mlx_hook(data.win_ptr, 17, 0, close_window, (void *)&data);
	mlx_key_hook(data.win_ptr, key_hook, (void *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
