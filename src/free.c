/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:14:56 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/16 11:09:08 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
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

void	free_img(t_dbt *dbt, void *mlx)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (dbt->img)
			mlx_destroy_image(mlx, dbt[i].img);
		i++;
	}
	return ;
}
