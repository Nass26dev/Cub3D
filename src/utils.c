/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:17:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/09 10:49:30 by tmarion          ###   ########.fr       */
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
		printf("%s\n", tab[i]);
		i++;
	}
}
