/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:27:45 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/11 14:16:00 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	fetch_color(t_data *data, const char c)
{
	size_t	i;
	size_t	start;
	int		r;
	int		g;
	int		b;

	i = 0;
	start = 0;
	while (data->textures[i][start] != c)
		i++;
	while (data->textures[i][start] < '0' || data->textures[i][start] > '9')
		start++;
	r = ft_atoi(data->textures[i] + start);
	while (data->textures[i][start] != ',')
		start++;
	start++;
	g = ft_atoi(data->textures[i] + start);
	while (data->textures[i][start] != ',')
		start++;
	b = ft_atoi(data->textures[i] + start + 1);
	return ((r << 16) | (g << 8) | b);
		// color = (r << 16) | (g << 8) | b; "|" operator decale les integer au rang de bit voulu pour tout stocker sur 24 bits dans l'ordre RGB
}

void	print_c_f(t_data *data)
{
	char			*pix;
	int				x;
	int				y;
	unsigned int	c_color;
	unsigned int	f_color;
	unsigned int	color_check;

	c_color = fetch_color(data, 'C');
	f_color = fetch_color(data, 'F');
	if (c_color == 1024 || f_color == 1024)
	{
		return ;
	}
	color_check = 0x000000;
	x = 0;
	y = 0;
	while (x < data->width)
	{
		while (color_check == 0x000000 && y < data->height)
		{
			pix = data->addr + (y * data->ll + x * (data->bpp / 8));
			color_check = *(unsigned int *)pix;
			if (color_check == 0x000000)
				*(unsigned int *)pix = c_color;
			y++;
		}
		color_check = 0x000000;
		x++;
		y = 0;
	}
	x = 0;
	y = data->height;
	while (x < data->width)
	{
		while (color_check == 0x000000 && y > 0)
		{
			pix = data->addr + (y * data->ll + x * (data->bpp / 8));
			color_check = *(unsigned int *)pix;
			if (color_check == 0x000000)
				*(unsigned int *)pix = f_color;
			y--;
		}
		color_check = 0x000000;
		x++;
		y = data->height;
	}
}

static int	get_size_text_file(const char *path, int count)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
		{
			i++;
			if(ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
				count ++;
			if (count == 2)
				break ;
			free(line);
		}
	}
	if (line)
		free(line);
	close(fd);
	return (i + 8);
}

char	**fetch_textures_file(const char *path, int count)
{
	char	**textures_file;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	textures_file = malloc(sizeof(char *) * get_size_text_file(path, 0) + 8);
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
		{
			textures_file[i] = line;
			i++;
			if(ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
				count ++;
			if (count == 2)
				break ;
		}
	}
	textures_file[i] = NULL;
	return (textures_file);
}

static char	*fetch_texture_path(t_data *data, const char *texture_id)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->textures[i])
	{
		if (ft_strncmp(texture_id, data->textures[i], 2) == 0)
		{
			while (data->textures[i][j] != '.' && data->textures[i][j])
				j++;
			return (ft_alloc_copy(data->textures[i] + j));
		}
		i++;
	}
	return (NULL);
}

int	get_texture(t_data *data)
{
	char	*path;
	size_t	i;
	int		fd;

	i = 0;
	data->dbt = malloc(sizeof(t_dbt) * 4);
	while (i < 4)
	{
		if (i == 0)
			path = fetch_texture_path(data, "NO");
		if (i == 1)
			path = fetch_texture_path(data, "SO");
		if (i == 2)
			path = fetch_texture_path(data, "WE");
		if (i == 3)
			path = fetch_texture_path(data, "EA");
		if (!path)
			return (1);
		path[ft_strlen(path) - 1] = 0;
		fd = open(path, O_RDONLY);
		if (fd == -1)
			return (1);
		close(fd);
		data->dbt[i].img = mlx_xpm_file_to_image(data->mlx_ptr, path,
				&data->dbt[i].width, &data->dbt[i].height);
		free(path);
		if (!data->dbt[i].img)
			return (printf("Failed to load xpm file\n"), 0);
		data->dbt[i].addr = mlx_get_data_addr(data->dbt[i].img, &data->dbt->bpp,
				&data->dbt->line_len, &data->dbt->endian);
		if (!data->dbt[i].addr)
			return (printf("Failed to fletch data addr\n"), 0);
		i++;
	}
	return (0);
}
