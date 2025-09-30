/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:04:11 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/30 16:43:32 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_rgb(char *str)
{
	size_t	i;
	int		r;
	int		g;
	int		b;

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
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (1);
	return (0);
}

static int	parse_color_args(char **text, int i, int j)
{
	size_t	comma;

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

static int	parse_map_horizontal(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (first_char(map[i]) != '1')
			return (1);
		i++;
	}
	i = 0;
	while (map[i])
	{
		if (last_char(map[i]) != '1')
			return (1);
		i++;
	}
	return (0);
}

static int	parse_map_vertical(char **map, size_t i, size_t j)
{
	while (map[i])
	{
		while (map[i][j] == 32)
			i++;
		if (map[i][j] == 10)
			break ;
		if (map[i][j] != '1')
			return (1);
		i = 0;
		j++;
	}
	j = 0;
	i = get_size_tab(map);
	while (map[i])
	{
		while (map[i][j] == 32)
			i--;
		if (map[i][j] == 0)
			return (0);
		if (map[i][j] != '1')
			return (1);
		i = get_size_tab(map);
		j++;
	}
	return (0);
}

int	parse_error(t_data *data)
{
	if (is_ceiling_color(data->textures) || is_floor_color(data->textures)
		|| is_text_paths(data->textures) || is_map(data->map)
		|| is_player(data->map))
	{
		data->error_msg = ft_strdup("Missing argument(s)");
		return (1);
	}
	if (parse_color_args(data->textures, 0, 0))
	{
		data->error_msg = ft_strdup("Wrong color's arguments");
		return (1);
	}
	if (parse_map_horizontal(data->map) || parse_map_vertical(data->map, 0, 0)
		|| is_valid_player(data->map) || is_valid_map(data->map))
	{
		data->error_msg = ft_strdup("Map is not valid");
		return (1);
	}
	return (0);
}
