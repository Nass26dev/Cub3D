/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:14:56 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:34 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void free_map(char **map)
{
	int i;

	i = 0;
	if (!map)
	{
		return;
	}
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	error_parse_cleanup(t_data *data)
{
	free_map(data->map);
	free_map(data->textures);
	free(data->error_msg);
	exit(EXIT_FAILURE);
}

int is_valid_fd(char *arg)
{
	int fd;

	if (!arg)
		return (1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return(1);
	}
	else
	{
		close(fd);
		return(0);
	}
}
