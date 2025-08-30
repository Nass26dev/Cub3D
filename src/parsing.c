/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:04:11 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/30 12:31:39 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int parse_rgb(char *str)
{
    size_t  i;
    int     r;
    int     g;
    int     b;

    i = 0;
    while (ft_isdigit(str[i]) == 0)
        i++;
    r = ft_atoi(str + i);
    while (ft_isdigit(str[i]))
        i++;
    i++;
    g = ft_atoi(str + i);
    while (ft_isdigit(str[i]))
        i++;
    i++;
    b = ft_atoi(str + i);
    // printf("%d  %d  %d\n", r, g, b);
    if (r < 0 || g < 0 || b < 0||
        r > 255 || g > 255 || b > 255)
        return (1);
    return (0);
}

static int parse_color_args(char **text, int i, int j)
{
    size_t  comma;

    comma = 0;
    while (text[i])
    {
        if (text[i][j] == 'F' || text[i][j] == 'C')
        {
            while (text[i][j] != '\n' && text[i][j])
            {
                j++;
                if (text[i][j] == ',')
                    comma++;
            }
            if (comma == 2)
                comma = parse_rgb(text[i]);
            else
                return (1);
            if (comma == 1)
                return (1);
            j = 0;
            comma = 0;
        }
        i++;
    }
    return (0);
}

int parse_error(t_data *data)//add custom msg avec char *error dans la structure
{
    if (parse_color_args(data->textures, 0, 0))
    {
        return (1);
    }
    return (0);
}
