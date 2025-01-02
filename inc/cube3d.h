#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include <limits.h>
#include "../mlx_linux/mlx.h"
#include "../libft/libft.h"

#define S_W 1900 // screen width
#define S_H 1000 // screen height

#define BLOCK 64

#define W 119
#define A 97
#define S 115
#define D 100

#define LEFT 65361
#define RIGHT 65363

#define PI 3.14159265359

#define TILE_SIZE 30 // tile size
#define FOV 60 // field of view
#define ROTATION_SPEED 0.045 // rotation speed
#define PLAYER_SPEED 4 // player speed

enum	e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_player
{
	float	p_x; // player x position in pixels
	float	p_y; // player y position in pixels
	float	p_tx; // player x position in tiles
	float	p_ty; // player y position in tiles
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	fov_rd;
	// Basic commands
	bool	key_up; // up key press flag
	bool	key_down; // down key press flag
	bool	key_left; // left key press flag
	bool	key_right; // right key press flag

	// Track rotation
	float	angle; // angle of rotation of the player
	bool 	left_rotate; // flag for when rotating left
	bool	right_rotate; // flag for when rotating right

}	t_player;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_color;

typedef struct s_img
{
	void	*mlx_img;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	int		*text_value;
}	t_texture;

typedef struct s_data
{
	char	**map2d; // the map
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;

	int p_x; // player x position
	int p_y; // player y position
	int w_map; // map width
	int h_map; // map height

	t_color	floor;
	t_color	ceiling;
}	t_data;

typedef	struct s_map
{
	int		p_init_pos[2];
	char	dir;
	char	**texture;
	char	**colors;
	int		**f_color;
	int		**c_color;
	int		f_alloc;
	int		c_alloc;
	char	**map;
	int		map_lines;
	int		h_map;
	int		w_map;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perpwalldist;

	double	side_dist_x;
	double	side_dist_y;

	int		wall_side; // the side of the wall we are looking at

	int		step_x;
	int		step_y;

	double	pos_x;
	double	pos_y;

	float	map_x;
	float	map_y;

	double	wall_x;
	double	tex_x;
	double	tex_y;
	double	step;
	double	tex_pos;

	int		start;
}	t_map;

typedef struct s_game
{
	void	*mlx; // ptr to mlx structure
	void	*win; // ptr to the window structure
	//void *img; // ptr to the image path
	t_img	img;

	// variables for the put_pixel function
	char *data;
	int bpp;
	int size_line;
	int endian;
	int flag;
	double ray_distance;
	double ray_angle;
	char	**map; // a copy of the map

	t_texture	texture_n;
	t_texture	texture_e;
	t_texture	texture_w;
	t_texture	texture_s;

	t_player	player; // an istance of the player structure
	//t_img		img;
	t_map		*map_ref;
	t_data		map_data;
}	t_game;

/////////////////////////////////////////////
// Prototypes
// Initialization :

void	init_map(t_map *map);
int		game_init(char **av, t_map *map, t_game *game);
void	init_player(t_player *player, t_map *map);
void	init_dir(t_map *map, t_player *player);
int		key_release(int keycode, t_player *player);
void	add_texture_info(t_game *game);
// Parsing
int		check_wall_char(t_map *map, int start, int end, int i, int j);
char	**check_and_read(char **av);
int		map_parsing(char **av, t_map *map);
char	**read_map(char *path);
int		get_map(char **tmp_map, t_map *map);
int		get_textures(char **tmp, t_map *map);
int		check_characters(t_map *map);
void	pos_or_dir(char c, int i, int j, t_map *map);
int		check_configuration(t_map *map);
//parsing utils
char	*cub3d_strdup(char *str);
int		out_map(char *line);
int		in_map(char *line);
int		in_texture(char *str);
int		count_line(int fd);
void	draw_map(t_game *game);
char	*tmp_num(char *tmp, char *texture);
int		line_is_empty(char *str);
char	**check_alloc_path(char *path);
int		check_texture_acces(char *texture, int i);
int		check_line_config(t_map *map, char *str);
int		check_colors(char *texture, char *str, int i, t_map *map);
int		loop_colors(t_map *map, char *tmp, int num, char *texture, char *str);
int		check_and_skip_range(char c, char *str, char *tmp, t_map *map, char type);
int		check_len_color(char *str);
void	alloc_colors(char type, int num, t_map *map);
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
float	distance(float x, float y);
char	**duplicate_double_pointer(char **original);
void	put_pixel2(int x, int y, int *color, t_game *game);
// controls
int		key_press(int keycode, t_player *player);
void	move_player(t_game *game);
int		key_release(int keycode, t_player *player);
int		exit_hook(t_game *game);
int		check_collision(t_game *game, int x, int y, int direction, int speed);
// rendering
int		draw_loop(t_game *game);
void	draw_line(t_player *player, t_game *game, float start_x, int i);
void draw_wall(t_game *game, int ray, int t_pix, int b_pix, double wall_h);
bool	touch(float px, float py, t_game *game);
void	create_textures(t_game *game, t_map *map);
void	render_background(t_game *game);
void	define_texture(t_game *game, int start, int line_height);
void	define_column(t_map *map, int *line_height, int *start, int *end);
void	img_pix_put(t_game *game, int x, int y, int color);
// debug
char	**save_map(void);
///////////////////////////////////////////////
void	print_map(char **map);
//free
void	free_map(t_map *map);
void	free_colors(t_map *map);
void	free_textures(t_game *game);
void	destroy_image(t_game *game);
