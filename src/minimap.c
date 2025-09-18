/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:10:24 by nass              #+#    #+#             */
/*   Updated: 2025/09/16 12:41:01 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	draw_square(t_data *data, int x, int y, unsigned int color)
{
	int	i;
	int	j;
	int	size;

	size = MINIMAP_SCALE;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	print_minimap(t_data *data)
{
	t_minimap	mp;

	mp.offset_x = data->width * 3 / 100;
	mp.offset_y = data->height * 5 / 100;
	mp.tile_size = MINIMAP_SCALE;
	mp.y = 0;
	while (mp.y < data->map_height)
	{
		mp.x = -1;
		while (++mp.x < data->map_width)
		{
			mp.tile = data->map[mp.y][mp.x];
			if (mp.tile == '1')
				mp.color = GRAY;
			else
				mp.color = WHITE;
			mp.draw_x = mp.offset_x + mp.x * mp.tile_size;
			mp.draw_y = mp.offset_y + mp.y * mp.tile_size;
			draw_square(data, mp.draw_x, mp.draw_y, mp.color);
		}
		mp.y++;
	}
	mp.player_draw_x = mp.offset_x + data->player_x * mp.tile_size;
	mp.player_draw_y = mp.offset_y + data->player_y * mp.tile_size;
	draw_square(data, mp.player_draw_x, mp.player_draw_y, RED);
}
