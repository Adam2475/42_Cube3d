#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../mlx_linux/mlx.h"
#include "../libft/libft.h"

#define S_W 1900 // screen width
#define S_H 1000 // screen height

#define W 119
#define A 97
#define S 115
#define D 100

#define PI 3.14159265359

#define TILE_SIZE 30 // tile size
#define FOV 60 // field of view
#define ROTATION_SPEED 0.045 // rotation speed
#define PLAYER_SPEED 4 // player speed

typedef struct s_player
{
	float	p_x; // player x position in pixels
	float	p_y; // player y position in pixels

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	// double angle; // player angle
	// float fov_rd; // field of view in radiants
	// int rot; // rotation
	// int l_r; // left right flag
	// int u_d; // up down flag
}	t_player;

typedef struct s_game
{
	void *mlx; // ptr to mlx structure
	void *win; // ptr to the window structure
	void *img; // ptr to the image path

	// variables for the put_pixel function
	char *data;
	int bpp;
	int size_line;
	int endian;

	t_player player; // an istance of the player structure
}	t_game;

typedef struct s_ray
{
	double ray_ngl; // ray angle
	double distance; // distance to the wall
	int flag; // flag for the wall
}	t_ray;

typedef struct s_data
{
	char **map2d; // the map
	int p_x; // player x position
	int p_y; // player y position
	int w_map; // map width
	int h_map; // map height
}	t_data;

typedef	struct s_map
{
	char	**texture;
	char	**colors;
	int		*f_color;
	int		*c_color;
	int		f_alloc;
	int		c_alloc;
	char	**map;
	int		texture_lines;
	int		total_lines;
}	t_map;

/////////////////////////////////////////
// Prototypes
// Initialization :

void	init_map(t_map *map);
int		game_init(char **av, t_map *map, t_game *game);
void	init_player(t_player *player);
int		key_release(int keycode, t_player *player);
// Parsing
int		map_parsing(char **av, t_map *map);
char	**read_map(char *path, t_map *map);
int		get_map(char **tmp_map, t_map *map);
int		get_textures(char **tmp, t_map *map);
int		check_characters(t_map *map);
//parsing utils
int		trim_line_textures(char *str);
char	*cub3d_strdup(char *str);
int		in_map(char *line);
int		count_line(int fd);
int		check_texture_acces(char *texture, int i);
int		check_line_config(t_map *map, char *str);
int		check_colors(char *texture, char *str, int i, t_map *map);
int		check_and_skip_range(char c, char *str, char *tmp, t_map *map, char type);
void	alloc_colors(char type, int len, int num, t_map *map);
// GNL 
char	*get_next_line(int fd);
char	*read_line(int fd, char *backup, char *buffer);
char	*divide_line(char **backup);
// utils
char	*strjoin_free(char *s1, char *s2);
void	free_matrix(char **matrix);
int		skip_spaces(char *str);
int		trim_spaces(char *str);
int		num_len(int n);
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
// controls
int		key_press(int keycode, t_player *player);
void	move_player(t_player *player);
int		key_release(int keycode, t_player *player);
int		exit_hook(t_player *player);
// rendering
int		draw_loop(t_game *game);
// debug
void	print_map(char **map);