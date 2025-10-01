/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:14:56 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/30 17:03:25 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (!*map)
	{
		free(map);
		return ;
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
	data->map = NULL;
	free_map(data->textures);
	data->textures = NULL;
	free(data->error_msg);
	return (0);
}

void	free_img(t_data *data, void *mlx)
{
	int	i;

	i = 0;
	if (data->text_bool == 0)
		data->text_index++;
	while (i < data->text_index)
	{
		if (data->dbt[i].img)
			mlx_destroy_image(mlx, data->dbt[i].img);
		i++;
	}
	return ;
}
