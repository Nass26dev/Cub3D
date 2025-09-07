/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:26:29 by tmarion           #+#    #+#             */
/*   Updated: 2025/09/02 14:43:45 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_valid_map(char **map)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            while (map[i][j] != first_char(map[i]))
                j++;
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' &&
                map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E')
                return (printf("invalid char: %d i: %zu j: %zu\n", map[i][j], i, j), 1);
            j++;
        }
        i++;
        j = 0;
    }
    return (0);
}
