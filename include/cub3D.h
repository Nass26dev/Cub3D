/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:02 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/11 13:17:34 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "../minilibx/mlx.h"
#include "../Libft/libft.h"

#define MOVE_SPEED 0.5
#define ROT_SPEED 0.1
#define MINIMAP_SCALE 10

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

typedef struct s_dbt // data base textures
{
	void *img;
	char *addr;
	int width;	// largeur
	int height; // hauteur
	int bpp;
	int line_len;
	int endian;
} t_dbt;

typedef struct s_point
{
	int x;
	int y;
	int	text_tab_len;
} t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*map_file;
	int		width;		// largeur screen
	int		height;		// hauteur screen
	int		map_height; // Hauteur de la map
	int		map_width;	// Largeur de la map
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	player_x; // Position du joueur en X
	double	player_y; // Position du joueur en Y
	char	*addr;		 // address of the image data
	int		bpp;		 // bits per pixel
	int		ll;			 // line length
	int		endian;		 // endianess
	char	**map;
	int		view_offset;
	char	**textures;
	int		c_color;
	int		f_color;
	char	*error_msg;
	struct s_point point;
	struct s_dbt *dbt; // data_base_textures
} t_data;

// utils.c
char	*ft_alloc_copy(const char *src);
void 	print_tab(char **tab);
int	get_size_tab(char **map);
// get_next_line.c
char	*get_next_line(int fd);
// raycast.c
void	render(t_data *data);
// print.c
void	print_line(t_data *data, t_dda *dda, t_raycast *rc, int x);
void	draw_square(t_data *data, int x, int y, int size, unsigned int color);
void	print_minimap(t_data *data);
// map.c
char	first_char(char *str);
char	**parse_file(const char *filename, t_data *data);
char	last_char(char *str);
// player.c
void	get_player_position(t_data *data);
// textures.c
int		get_texture(t_data *data);
void	print_c_f(t_data *data);
char	**fetch_textures_file(const char *path, int count);
// parsing.c
int		parse_error(t_data *data);
// is_here.c
int		is_ceiling_color(char **text);
int		is_floor_color(char **text);
int		is_text_paths(char **text);
int		is_map(char **map);
int		is_player(char **map);
//is_valid.c
int is_valid_player(char **map);
int is_valid_map(char **map);
int is_val_char(char c);
//free.c
void	free_map(char **map);
int		error_parse_cleanup(t_data *data);

#endif
