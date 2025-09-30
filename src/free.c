/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:14:56 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/30 11:07:04 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map || !(*map))
		return ;
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
