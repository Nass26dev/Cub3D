/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:27:45 by tmarion           #+#    #+#             */
/*   Updated: 2025/08/18 15:34:11 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char **fetch_textures_file(const char *path)
{
    char **textures_file;
    char *line;
    int  fd;
    int  i;

    i = 0;
    textures_file = malloc(sizeof(char *) * 9);
    fd = open(path, O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line || first_char(line) == '1')
            break;
        else
        {
            textures_file[i] = line;
            i++;
        }
    }
    textures_file[i] = NULL;
    return (textures_file);
}

static char *fetch_texture_path(t_data *data, const char *texture_id)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (data->textures[i])
    {
        if (ft_strncmp(texture_id, data->textures[i], 2) == 0)
        {
            while (data->textures[i][j] != '.' && data->textures[i][j])
                j++;
            
            return (ft_alloc_copy(data->textures[i] + j));
        }
        i++;
    }
    return (NULL);
}


int get_texture(t_data *data)
{
    char    *path;
    size_t  i;

    i = 0;
    data->dbt = malloc(sizeof(t_dbt) * 4);

    while (i < 4)
    {
        if (i == 0)
            path = fetch_texture_path(data, "NO");
        if (i == 1)
            path = fetch_texture_path(data, "SO");
        if (i == 2)
            path = fetch_texture_path(data, "WE");
        if (i == 3)
            path = fetch_texture_path(data, "EA");
        path[ft_strlen(path) - 1] = 0;
        data->dbt[i].img = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->dbt[i].width, &data->dbt[i].height);
        if (!data->dbt[i].img)
            return(printf("Failed to load xpm file\n"), 0);
        data->dbt[i].addr = mlx_get_data_addr(data->dbt[i].img, &data->dbt->bpp, &data->dbt->line_len, &data->dbt->endian);
        if (!data->dbt[i].addr)
            return(printf("Failed to fletch data addr\n"), 0);
        i++;
    }
    // printf("NO----|%s|\n", path);
    return (1);
}


// static char **fetch_texture_data(const char *path)
// {
//     t_point point;
//     int     fd_texture;
//     char    *line;
//     char    **xpm_data;

//     fd_texture = open(path, O_RDONLY);
//     if (fd_texture == -1)
//         return (printf("\n1\n"), NULL);
//     point = get_point(fd_texture);
//     close(fd_texture);
//     fd_texture = open(path, O_RDONLY);
//     if (fd_texture == -1)
//         return (printf("\n2\n"), NULL);
//     xpm_data = malloc(sizeof(char *) * (point.y + 1));
//     point.y = 0;
//     while (1)
//     {
//         line = get_next_line(fd_texture);
//         if (!line)
//             break;
//         else
//         {
//             xpm_data[point.y] = line;
//             point.y++;
//         }
//     }
//     xpm_data[point.y] = NULL;
//     close(fd_texture);
//     return (xpm_data);
// }
