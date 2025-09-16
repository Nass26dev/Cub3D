/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:59:53 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/12 15:37:48 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_data *data, int x, int y, int size, unsigned int color)
{
	int	i;
	int	j;

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

static int	remap_val(int value, int start1, int stop1, int start2, int stop2)
{
	int	val_remap;

	val_remap = (float)(value - start1) / (stop1 - start1) * (stop2 - start2);
	return (val_remap);
}

void	print_line(t_data *data, t_dda *dda, t_raycast *rc, int x)
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	char			*adr;
	unsigned int	color;
	double			wallX;
	int				texYpos;
	char			*dst;
	int				texXpos;

	(void)rc;
	adr = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->ll,
			&data->endian);
	line_height = (int)(data->height / dda->wall_dist);
	draw_start = -line_height / 2 + data->height / 2 + data->view_offset;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->height / 2 + data->view_offset;
	if (draw_end >= data->height)
		draw_end = data->height - 1;
	for (int y = draw_start; y < draw_end; y++)
	{
		if (dda->side == 0)
			wallX = rc->map_y + dda->wall_dist * rc->ray_dir_y;
		else
			wallX = rc->map_x + dda->wall_dist * rc->ray_dir_x;
		wallX = wallX - floor(wallX);
		texXpos = (int)(wallX * (double)data->dbt[0].width);
		texYpos = remap_val(y, draw_start, draw_end, 0, data->dbt[0].height);
		if (dda->side == 0)
		{
			if (rc->ray_dir_x < 0)
				color = ((int *)data->dbt[2].addr)[texXpos % data->dbt[2].width
					+ texYpos * data->dbt[2].width];
			else
				color = ((int *)data->dbt[3].addr)[texXpos % data->dbt[3].width
					+ texYpos * data->dbt[3].width];
		}
		else
		{
			if (rc->ray_dir_y > 0)
				color = ((int *)data->dbt[1].addr)[texXpos % data->dbt[1].width
					+ texYpos * data->dbt[1].width];
			else
				color = ((int *)data->dbt[0].addr)[texXpos % data->dbt[0].width
					+ texYpos * data->dbt[0].width];
		}
		dst = adr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
