/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:26:29 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/09 16:55:29 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static int get_size(char **map)
// {
//     size_t  i;

//     i = 0;
//     while (map[i])
//         i++;
//     return (i);
// }

int is_valid_player(char **map)
{
    size_t  i;
    size_t  j;
    size_t  count;

    i = 0;
    j = 0;
    count = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                count++;
            j++;
        }
        i++;
        j = 0;
    }
    if (count != 1)
        return (1);
    return (0);
}

int is_valid_map(char **map)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' &&
                map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' &&
                map[i][j] != 32)
                return (printf("char: %d", map[i][j]), 1);
            j++;
        }
        i++;
        j = 0;
    }
    return (0);
}
