/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:02 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/29 13:33:13 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "../minilibx/mlx.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*map_file;
	int		width;
	int		height;
	char	*addr; // address of the image data
	int 	bpp; // bits per pixel
	int 	ll; // line length
	int 	endian; // endianess
	char	**map;
}			t_data;

typedef struct s_point
{
	int x;
	int y;
}			t_point;

// utils.c 
ssize_t ft_strlen(const char *s);
// get_next_line.c
char				*get_next_line(int fd);
#endif
