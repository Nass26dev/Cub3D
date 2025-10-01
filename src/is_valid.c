/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:26:29 by tmarion           #+#    #+#             */
/*   Updated: 2025/10/01 18:25:47 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_val_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 32 || c == 10)
		return (0);
	return (1);
}

static int	is_val_parse_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

static int	check_arround(char **map, size_t i, size_t j)
{
	if (!map[i + 1][j] || !map[i - 1][j] || !map[i][j + 1] || !map[i][j - 1])
		return (1);
	if (is_val_parse_char(map[i + 1][j]) || is_val_parse_char(map[i - 1][j])
		|| is_val_parse_char(map[i][j + 1]) || is_val_parse_char(map[i][j - 1]))
		return (1);
	return (0);
}

int	is_valid_player(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
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

int	is_valid_map(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (is_val_char(map[i][j]))
				return (1);
			if (map[i][j] == '0')
			{
				if (check_arround(map, i, j))
					return (1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
