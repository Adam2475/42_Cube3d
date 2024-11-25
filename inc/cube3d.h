#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../mlx_linux/mlx.h"

#define S_W 1900 // screen width
#define S_H 1000 // screen height
#define TILE_SIZE 30 // tile size
#define FOV 60 // field of view
#define ROTATION_SPEED 0.045 // rotation speed
#define PLAYER_SPEED 4 // player speed

typedef struct s_player
{
	int p_x; // player x position in pixels
	int p_y; // player y position in pixels
	double angle; // player angle
	float fov_rd; // field of view in radiants
	int rot; // rotation
	int l_r; // left right flag
	int u_d; // up down flag
}	t_player;

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

/////////////////////////////////////////
// Prototypes
// Initialization :
int	map_initialization(char **av);