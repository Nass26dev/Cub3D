/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:59:53 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/09 11:55:09 by tmarion          ###   ########.fr       */
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

void print_line(t_data *data, t_dda *dda, int x)
{
	int line_height;
	int draw_start; 
	int draw_end;
    void    *img;
    char    *adr;

    img = get_texture(data, "NO");
    if (!img)
    {
        printf("\n Failed to load xpm\n");
        return ;
    }
    adr = mlx_get_data_addr(img, &data->bpp, &data->ll, &data->endian);
	line_height = (int)(data->height / dda->wall_dist);
	draw_start = -line_height / 2 + data->height / 2 + data->view_offset;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->height / 2 + data->view_offset;
	if (draw_end >= data->height)
		draw_end = data->height - 1;
	
	unsigned int color = (dda->side == 1) ? 0x00FF00 : 0xFF0000;
	
	for (int y = draw_start; y < draw_end; y++)
	{
		char *dst = adr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
