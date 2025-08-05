/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:02 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/05 14:48:43 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../minilibx/mlx.h"

#define MOVE_SPEED 0.5
#define ROT_SPEED 0.1
typedef struct s_dda
{
	int step_x;
	int step_y;
	double side_dist_x;
	double side_dist_y;
	int hit;
	int side;
	double wall_dist;
} t_dda;

typedef struct s_raycast
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double delta_x;
	double delta_y;
	int map_x;
	int map_y;
} t_raycast;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*map_file;
	int		width;
	int		height;
	int 	map_height; // Hauteur de la map
	int 	map_width; // Largeur de la map
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double		player_x; // Position du joueur en X
	double		player_y; // Position du joueur en Y
	char	*addr; // address of the image data
	int 	bpp; // bits per pixel
	int 	ll; // line length
	int 	endian; // endianess
	char	**map;
	int move_forward;
	int move_backward;
	int strafe_left;
	int strafe_right;
	int rotate_left;
	int rotate_right;
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
