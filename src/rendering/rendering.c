/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:16:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/18 16:24:21 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// static	void	img_pix_put(t_map *map, int x, int y, int color)
// {
// 	char	*pixel;

// 	if (y < 0 || y > S_H - 1 || x < 0
// 		|| x > S_W - 1)
// 		return ;
// 	pixel = (map->img[4].addr + (y * map->img[4].line_len
// 				+ x * (map->img[4].bpp / 8)));
// 	*(int *)pixel = color;
// }

// int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

void	render_background(t_game *game)
{
	t_map *map = game->map_ref;
	int	x;
	int	y;
	int color_f[3];
	int color_c[3];

	color_f[0] = *map->f_color[0];
	color_f[1] = *map->f_color[1];
	color_f[2] = *map->f_color[2];
	color_c[0] = *map->c_color[0];
	color_c[1] = *map->c_color[1];
	color_c[2] = *map->c_color[2];
	x = 0;
	while (x < S_W)
	{
		y = 0;
		while (y < (S_H - 1))
		{
			if (y < (S_H / 2))
				img_pix_put(game, x, y++, create_trgb(0, color_c[0],
						color_c[1], color_c[2]));
			else
				img_pix_put(game, x, y++, create_trgb(0, color_f[0],
						color_f[1], color_f[2]));
		}
		x++;
	}
}

static	void	get_delta_dist(t_map *map)
{
	if (map->ray_dir_x == 0)
		map->delta_dist_x = 1e30;
	else
		map->delta_dist_x = fabs(1 / map->ray_dir_x);
	if (map->ray_dir_y == 0)
		map->delta_dist_y = 1e30;
	else
		map->delta_dist_y = fabs(1 / map->ray_dir_y);
}

static void	digital_differential_analyser(t_map *map)
{
	int	wall;
	

	wall = 0;
	while (wall == 0)
	{
		if (map->side_dist_x < map->side_dist_y)
		{
			map->side_dist_x += map->delta_dist_x;
			map->map_x += map->step_x;
			map->wall_side = 0;
		}
		else
		{
			map->side_dist_y += map->delta_dist_y;
			map->map_y += map->step_y;
			map->wall_side = 1;
		}
		if (map->map[(int)(map->map_y)][(int)map->map_x] == '1')
			wall = 1;
	}
}

static void	get_step(t_map *map, t_player *player)
{
	if (map->ray_dir_x < 0)
	{
		map->step_x = -1;
		map->side_dist_x = (map->pos_x - player->p_x) * map->delta_dist_x;
	}
	else
	{
		map->step_x = 1;
		map->side_dist_x = (map->map_x + 1.0 - player->p_x) * map->delta_dist_x;
	}
	if (map->ray_dir_y < 0)
	{
		map->step_y = -1;
		map->side_dist_y = (map->pos_y - player->p_y) * map->delta_dist_y;
	}
	else
	{
		map->step_y = 1;
		map->side_dist_y = (map->map_y + 1.0 - player->p_y) * map->delta_dist_y;
	}
}

static	int	get_color(t_game *game, int x, int y, int i)
{
	if (i == 0)
		return (*(int *)(game->texture_n.img.mlx_img + (y * game->texture_n.img.line_len + x * (game->texture_n.img.bpp / 8))));
	else if (i == 1)
		return (*(int *)(game->texture_s.img.mlx_img + (y * game->texture_s.img.line_len + x * (game->texture_s.img.bpp / 8))));
	else if (i == 2)
		return (*(int *)(game->texture_e.img.mlx_img + (y * game->texture_e.img.line_len + x * (game->texture_e.img.bpp / 8))));
	else if (i == 3)
		return (*(int *)(game->texture_w.img.mlx_img + (y * game->texture_w.img.line_len + x * (game->texture_w.img.bpp / 8))));
	return (0);
}

void	img_pix_put(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > S_H - 1 || x < 0
		|| x > S_W - 1)
		return ;
	pixel = (game->img.addr + (y * game->img.line_len
				+ x * (game->img.bpp / 8)));
	*(int *)pixel = color;
}

static	void	draw(t_game *game, int x, int texture)
{
	int	color;

	//printf("tex_x: %f\n", game->map_ref->tex_x);
	//printf("tex_y: %f\n", game->map_ref->tex_y);
	color = get_color(game, game->map_ref->tex_x, game->map_ref->tex_y, texture);
	//printf("%d\n", color);
	//exit(1);
	img_pix_put(game, x, game->map_ref->start, color);
}

/**
 * 	arrivare ad avere i muri con 4 colori 
 * 					- e' giusto che guardi l angolo del player per capire il lato colpito
 *	devi prendere la posizione nella tile della mappa dove il raggio colpisce
 * 	devi mappare la posizione colpita con la posizione nella texture(questo lo fai con le proporzioni    se 64 : 128 = 128 : 256 )
 * 	una volta che hai il pixel e la poszione nella texture
 * 	devi scorrere la texture in verticale e inserirli nell immagine mlx->img
 * 
 * 
 * 
 * 
 * 
 * 
 */



static	void	draw_column(t_player *player, t_game *game, float start_x, float start_y, int i, int end)
{
	 int color[3];
	 int	line_height;

	 //define_column(game->map_ref, &line_height, map->start, map->end);
	 color[0] = 89;
	 color[1] = 153;
	 color[2] = 53;
	 //printf("%s\n", game->img.addr);
	//  while (start_y < end)
	//  {
	//  	//put_pixel2(i, start_y++, color, game);  //Renders the walls in 3d
	//  	game->map_ref->tex_y = (int)game->map_ref->tex_pos & (128 - 1);
	//  	game->map_ref->tex_pos += game->map_ref->step;
	// 	// printf("%d\n", game->map_ref->wall_side);
	// 	// printf("%f\n", game->map_ref->ray_dir_y);
	// 	// printf("%f\n", game->map_ref->ray_dir_x);
	//  	// if (game->map_ref->wall_side == 1 && game->map_ref->ray_dir_y < 0)
	//  	// 	img_pix_put(game, i, start_y, SOUTH);
	//  	// if (game->map_ref->wall_side == 1 && game->map_ref->ray_dir_y > 0)
	//  	// 	img_pix_put(game, i, start_y, NORTH);
	//  	// if (game->map_ref->wall_side == 0 && game->map_ref->ray_dir_x < 0)
	//  	// 	img_pix_put(game, i, start_y, WEST);
	//  	// if (game->map_ref->wall_side == 0 && game->map_ref->ray_dir_x > 0)
	//  	// 	img_pix_put(game, i, start_y, EAST);
	// 	// if (game->map_ref->wall_side == 1 && game->map_ref->ray_dir_y < 0)
	//  	// 	draw(game, start_y++, SOUTH);
	//  	// if (game->map_ref->wall_side == 1 && game->map_ref->ray_dir_y > 0)
	//  	// 	draw(game, start_y++, NORTH);
	//  	// if (game->map_ref->wall_side == 0 && game->map_ref->ray_dir_x < 0)
	//  	// 	draw(game, start_y++, WEST);
	//  	// if (game->map_ref->wall_side == 0 && game->map_ref->ray_dir_x > 0)
	//  	// 	draw(game, start_y++, EAST);
	//  	//put_pixel2(i, start_y, color, game);
	//  	start_y++;
	//  }
	printf("wall side: %d\n", game->map_ref->wall_side);
	printf("ray_dir_x: %f\n", game->map_ref->ray_dir_x);
	printf("ray_dir_y: %f\n", game->map_ref->ray_dir_y);
	while (start_y < end)
	{
		img_pix_put(game, i, start_y++,  0x0); // Renders the walls in 3d
	}
}


void	define_column(t_map *map, int *line_height, int *start, int *end)
{
	*line_height = S_H / map->perpwalldist;
	*start = -*line_height / 2 + S_H / 2;
	if (*start < 0)
		*start = 0;
	*end = *line_height / 2 + S_H / 2;
	if (*end >= S_H)
		*end = S_H - 1;
}

// function called for every point x to draw the column
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	// init the starting point of the ray
	float ray_x = player->p_x;
	float ray_y = player->p_y;

	// touch check if a collision happens at a given angle
	while (!touch(ray_x, ray_y, game))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	//printf("ray_x: %f\n", ray_x);
	//printf("ray_y: %f\n", ray_y);
	
	float dist = distance(ray_x - player->p_x, ray_y - player->p_y);
	//printf("%f\n", dist);
	float height = (BLOCK / dist) * (S_W / 2);
	
	int start_y = (S_H - height) / 2;
	int end = start_y + height;
	//printf("start %d end %d \n", start_y, end);
	int line_height = 0;
	int end2 = 0;
	//int start;
	//game->map_ref->wall_side = 0;
	game->map_ref->ray_dir_x = cos(ray_x);
	game->map_ref->ray_dir_y = cos(ray_y);
	//get_delta_dist(game->map_ref);
	//game->map_ref->map_x = player->p_x;
	//game->map_ref->map_y = player->p_y;
	get_step(game->map_ref, player);
	digital_differential_analyser(game->map_ref);
	//if (game->map_ref->wall_side == 0)
	//	game->map_ref->perpwalldist = ((game->map_ref->side_dist_x - game->map_ref->delta_dist_x));
	//else
	//	game->map_ref->perpwalldist = ((game->map_ref->side_dist_y - game->map_ref->delta_dist_y));
	define_column(game->map_ref, &line_height, &game->map_ref->start, &end2);
	//printf("%f\n", game->map_ref->perpwalldist); */
	define_texture(game, game->map_ref->start, line_height); 
	// TODO : Starting texture rendering
	//printf("%d\n", game->map_ref->wall_side);
	//printf("%f\n", game->map_ref->ray_dir_y);
	//printf("%f\n", game->map_ref->ray_dir_x);
	draw_column(player, game, start_x, start_y, i, end);
}
