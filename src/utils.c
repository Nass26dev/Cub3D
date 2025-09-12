/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:17:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/12 13:45:14 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_alloc_copy(const char *src)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(src) + 1);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

void	print_tab(char **tab)
{
	size_t	i;

	i = 0;
	printf("\nTab printing...\n");
	while (tab[i])
	{
		printf("[%zu][%s]\n", i, tab[i]);
		i++;
	}
	printf("\nEnd printing...\n");
}

int	get_size_tab(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i - 1);
}
