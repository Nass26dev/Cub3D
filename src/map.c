/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:03:35 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/07 10:12:06 by tmarion          ###   ########.fr       */
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
