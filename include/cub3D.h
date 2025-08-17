/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:02 by nyousfi           #+#    #+#             */
/*   Updated: 2025/08/08 16:46:41 by tmarion          ###   ########.fr       */
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
#include "../Libft/libft.h"

#define MOVE_SPEED 0.5
#define ROT_SPEED 0.1
#define MINIMAP_SCALE 20

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
	double 	dir_x;
	double 	dir_y;
	double	plane_x;
	double	plane_y;
	double	player_x; // Position du joueur en X
	double	player_y; // Position du joueur en Y
	char	*addr; // address of the image data
	int 	bpp; // bits per pixel
	int 	ll; // line length
	int 	endian; // endianess
	char	**map;
	int 	view_offset;
	char	**textures;
}			t_data;

typedef struct s_point
{
	int x;
	int y;
}			t_point;

// utils.c 
char	*ft_alloc_copy(const char *src);
void	print_tab(char **tab);
// get_next_line.c
char				*get_next_line(int fd);
//raycast.c 
void render(t_data *data);
// print.c
void print_line(t_data *data, t_dda *dda, int x);
void draw_square(t_data *data, int x, int y, int size, unsigned int color);
void print_minimap(t_data *data);
// map.c
void free_map(char **map);
char	first_char(char *str);
char **parse_file(const char *filename, t_data *data);
t_point get_point(int fd);
// player.c
void get_player_position(t_data *data);
//textures
void *get_texture(t_data *data, const char *texture_id);
char **fetch_textures_file(const char *path);

#endif


/*
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
NOSWEA
*/