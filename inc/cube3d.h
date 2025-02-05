/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:53:53 by giulio            #+#    #+#             */
/*   Updated: 2025/02/05 12:09:11 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include "../mlx_linux/mlx.h"
#include "../libft/libft.h"

#define S_W 1900
#define S_H 1000
#define BLOCK 32
#define W 119
#define A 97
#define S 115
#define D 100
#define ESC 65307
#define LEFT 65361
#define RIGHT 65363
#define PI 3.14159265359
#define TILE_SIZE 32
#define FOV 60
#define ROTATION_SPEED 0.045
#define PLAYER_SPEED 4

#define TARGET_FPS 100
#define FRAME_TIME_MS 10

typedef struct s_player
{
	float	p_x;
	float	p_y;
	float	plane_x;
	float	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	fov_rd;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	float	angle;
	bool	left_rotate;
	bool	right_rotate;

}	t_player;

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
	char	**map2d;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
}	t_data;

typedef struct s_map
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
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			flag;
	double		ray_distance;
	double		ray_angle;
	double		wall_h;
	char		**map;
	t_img		img;
	t_texture	texture_n;
	t_texture	texture_e;
	t_texture	texture_w;
	t_texture	texture_s;
	t_player	player;
	t_map		*map_ref;
	t_data		map_data;
}	t_game;

void	init_map(t_map *map);
int		game_init(char **av, t_map *map, t_game *game);
void	init_player(t_player *player, t_map *map);
void	init_dir(t_map *map, t_player *player);
int		check_fist_and_last_wall(t_map *s_map, int i, int end, int start);
int		first_other_walls(t_map *s_map, char **map, int i, int space);
int		first_check_wall(char **map, int i, int end, int start);
int		last_other_walls(t_map *s_map, char **map, int i, int space);
int		last_check_wall(char **map, int i, int end, int start);
int		key_release(int keycode, t_player *player);
void	init_struct(t_game *game);
void	assign_texture_path(t_game *game, t_map *map);
int		check_char(t_map *map, int start, int end, int i);
int		check_other_wall(t_map *map, int i, int j);
char	**check_and_read(char **av);
int		map_parsing(char **av, t_map *map);
char	**read_map(char *path);
int		get_map(char **tmp_map, t_map *map);
int		get_textures(char **tmp, t_map *map);
int		check_characters(t_map *map);
void	pos_or_dir(char c, int i, int j, t_map *map);
int		check_configuration(t_map *map);
int		check_map_h_w(t_map *map);
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
int		loop_colors(t_map *map, char *tmp, char *texture, char *str);
int		check_and_skip_range(char *str, char *tmp, t_map *map, char type);
int		check_len_color(char *str);
void	alloc_colors(char type, int num, t_map *map);
char	*get_next_line(int fd);
char	*read_line(int fd, char *backup, char *buffer);
char	*divide_line(char **backup);
char	*strjoin_free(char *s1, char *s2);
void	free_matrix(char **matrix);
int		skip_spaces(char *str);
int		trim_spaces(char *str);
int		num_len(int n);
void	put_pixel(int x, int y, int color, t_game *game);
char	**duplicate_double_pointer(char **original);
void	put_pixel2(int x, int y, int *color, t_game *game);
int		ft_strnlen(char *str, int n);
int		key_press(int keycode, t_game *game);
void	move_player(t_game *game);
int		key_release(int keycode, t_player *player);
int		exit_hook(t_game *game);
int		check_collision(t_game *game, int direction);
int		draw_loop(t_game *game);
void	draw_wall(t_game *game, int ray, int t_pix, int b_pix);
void	create_textures(t_game *game, t_map *map);
void	render_background(t_game *game);
void	img_pix_put(t_game *game, int x, int y, int color);
float	nor_angle(float angle);
double	normalize_to_one(double num);
int		int_imax(int n1, int n2);
int		get_texture_color(t_img *texture, int x, int y);
int		calc_tex_x(t_game *game, t_img *texture, int flag);
int		calc_tex_y(t_img *texture, double tex_pos);
double	calc_wall_px_hit(t_game *game, int flag);
t_img	*define_side(t_game *game);
void	print_map(char **map);
void	free_map(t_map *map);
void	free_colors(t_map *map);
void	free_textures(t_game *game);
void	destroy_image(t_game *game);
float	get_v_inter(t_player *player, t_map *map, float angl);
float	get_h_inter(t_player *player, t_map *map, float angl);
int		wall_hit(float x, float y, t_map *map);
void	clear_image(t_game *game);
int		inter_check(float angle, float *inter, float *step, int is_horizon);
int		unit_circle(float angle, char c);
void	handle_player_movement(t_game *game,
			float cos_angle, float sin_angle, int speed);
int		check_direction_up(t_game *game, int code);
int		check_direction_down(t_game *game, int code);
int		check_left(t_game *game);
int		check_direction_left(t_game *game, int code);
int		check_direction_right(t_game *game, int code);
int		mini_helper2(t_game *game, int tmp_x, int tmp_y);