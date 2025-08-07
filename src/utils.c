/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:17:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/07 17:24:31 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

ssize_t ft_strlen(const char *s)
{
	ssize_t len = 0;

	while (s[len] != '\0')
		len++;
	return len;
}

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
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
