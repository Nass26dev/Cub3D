/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:59:53 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/23 14:39:59 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	int i;
	int j;
	
	i = 0;
    while(i < size)
    {
		j = 0;
        while(j < size)
		{
            draw_pixel(data, x + j, y + i, color);
			j++;
		}
		i++;
    }
}

static int remap_val(int value, int start1, int stop1, int start2, int stop2)
{
    int outgoing = (float)(value - start1) / (stop1 - start1) * (stop2 - start2);
    return outgoing;
}

void print_line(t_data *data, t_dda *dda, t_raycast *rc, int x)
{
	int line_height;
	int draw_start;
	int draw_end;
    char    *adr;
	unsigned int color;

    (void)rc;
    adr = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->ll, &data->endian);
	line_height = (int)(data->height / dda->wall_dist);
	draw_start = -line_height / 2 + data->height / 2 + data->view_offset;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->height / 2 + data->view_offset;
	if (draw_end >= data->height)
		draw_end = data->height - 1;

    for (int y = draw_start; y < draw_end; y++)
    {
        int texYpos = remap_val(y, draw_start, draw_end, 0, data->dbt[0].height);
        int texXpos = x;
        if (dda->side == 0)
        {
            if (rc->ray_dir_x < 0)//ouest
                color = ((int *)data->dbt[2].addr)[texXpos % data->dbt[2].width + texYpos * data->dbt[2].width];
            else//est
                color = ((int *)data->dbt[3].addr)[texXpos % data->dbt[3].width + texYpos * data->dbt[3].width];
        }
        else
        {
            if (rc->ray_dir_x > 0)//sud
                color = ((int *)data->dbt[1].addr)[texXpos % data->dbt[1].width + texYpos * data->dbt[1].width];
            else//nord
                color = ((int *)data->dbt[0].addr)[texXpos % data->dbt[0].width + texYpos * data->dbt[0].width];
        }
        char *dst = adr + (y * data->ll + x * (data->bpp / 8));
        *(unsigned int *)dst = color;
    }
}
/*
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.index = WEST;
		else
			data->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.index = SOUTH;
		else
			data->texinfo.index = NORTH;
	}
*/

/*
N --> x = 0 / y = -1
-------------------------> x = -0.5 / y = -0.5
W --> x = -1 / y = 0
-------------------------> x = -0.5 / y = 0.5
S --> x = 0 / y = 1
-------------------------> x = 0.5 / y = 0.5
E --> x = 1 / y = 0
-------------------------> x = 0.5 / y = -0.5
N --> x = 0 / y = -1
*/