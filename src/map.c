/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:03:35 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/02 14:01:22 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	first_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == 9 || str[i] == 32)
		i++;
	return (str[i]);
}

char	last_char(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (str[i] == 9 || str[i] == 32 || str[i] == '\n')
		i--;
	return (str[i]);
}


static t_point get_point(int fd, char **text, size_t i)
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
		if (point.y == 0 && first_char(line) == '1')
			point.x = ft_strlen(line) - 1;
		if (first_char(line) == '1')
			point.y++;
		free(line);
	}
	while (text[i])
		i++;
	point.text_tab_len = i;
	return (point);
}

char **get_map(int fd, t_point point, int i, int count)
{
	char **map;
	char *line;

	map = malloc(sizeof(char *) * (point.y + 1));
	if (!map)
		return (NULL);
	while (i < point.y)
	{
		line = get_next_line(fd);
		count++;
		if (!line)
			break;
		if ((first_char(line) != '1' && first_char(line) != '0' &&
			first_char(line) != 'N' && first_char(line) != 'W' &&
			first_char(line) != 'S' && first_char(line) != 'E') ||
			count < point.text_tab_len)
			continue ;
		else
		{
			map[i] = line;
			i++;
		}
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
	point = get_point(fd, data->textures, 0);
	data->point = point;
	data->map_height = point.y;
	data->map_width = point.x;
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	map = get_map(fd, point, 0, 0);
	close(fd);
	return (map);
}
