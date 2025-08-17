/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:27:45 by tmarion           #+#    #+#             */
/*   Updated: 2025/08/09 12:02:19 by tmarion          ###   ########.fr       */
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
            return (ft_alloc_copy(data->textures[i] +j));
        }
        i++;
    }
    return (NULL);
}


void *get_texture(t_data *data, const char *texture_id)
{
    char *path;
    void *img;
    int  height;//hauteur
    int  width;//largeur

    path = fetch_texture_path(data, texture_id);
    printf("\n%s_PATHS:  %s\n",texture_id, path);
    if (!path)
        return (NULL);
    img = mlx_xpm_file_to_image(data->mlx_ptr, path, &width, &height);
    if (!img)
        return (NULL);
    return (img);
    
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
