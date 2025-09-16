/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:18:02 by nyousfi           #+#    #+#             */
/*   Updated: 2025/09/16 13:19:05 by tmarion          ###   ########.fr       */
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
#define W_PRESS 119
#define S_PRESS 115
#define A_PRESS 97
#define D_PRESS 100
#define ESC_PRESS 65307
#define RIGHT_ARROW_PRESS 65361
#define LEFT_ARROW_PRESS 65363
#define UP_ARROW_PRESS 65362
#define DOWN_ARROW_PRESS 65364
#define RED 0xFF0000
#define GRAY 0x777777
#define WHITE 0xFFFFFF
#define WALL_DIST_CALC_SIDE_0 (rc->map_x - data->player_x + (1 - dda.step_x) / 2) / rc->ray_dir_x
#define WALL_DIST_CALC_SIDE_1 (rc->map_y - data->player_y + (1 - dda.step_y) / 2) / rc->ray_dir_y

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

typedef struct s_dbt
{
	void *img;
	char *addr;
	int width;
	int height;
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

typedef struct s_minimap
{
	int		offset_x;
	int		offset_y;
	char	tile;
	unsigned int color;
	int		draw_x;
	int		draw_y;
	int		player_draw_x;
	int		player_draw_y;
	int tile_size;
	int x;
	int y;
}		t_minimap;

typedef struct s_render
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	char			*adr;
	unsigned int	color;
	double			wallX;
	int				texYpos;
	char			*dst;
	int				texXpos;
}		t_render;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*map_file;
	int		width;
	int		height;
	int		map_height;
	int		map_width;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	player_x;
	double	player_y;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	char	**map;
	int		view_offset;
	char	**textures;
	int		c_color;
	int		f_color;
	char	*error_msg;
	struct s_point point;
	struct s_dbt *dbt;
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
void	print_minimap(t_data *data);
// map.c
char	first_char(char *str);
char	**parse_file(const char *filename, t_data *data);
char	last_char(char *str);
// player.c
void	get_player_position(t_data *data);
// textures.c
int		get_texture(t_data *data, size_t i, char *path);
void	print_c_f(t_data *data, int x, int y);
char	**fetch_textures_file(const char *path, int count, int i);
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
void	free_img(t_dbt *dbt, void *mlx);
//launch.c
bool check_args(t_data *data, char **argv);
bool manage_map(t_data *data, char **argv);
void init_mlx(t_data *data);
//movement_keypress.c
bool	manage_w(t_data *data);
bool	manage_s(t_data *data);
bool	manage_a(t_data *data);
bool	manage_d(t_data *data);
//view_keypress.c
bool	manage_ra(t_data *data);
bool	manage_la(t_data *data);
bool	manage_da(t_data *data);
bool	manage_ua(t_data *data);
//map_utils.c
bool is_ok(char *line, int count, t_point point);

#endif
