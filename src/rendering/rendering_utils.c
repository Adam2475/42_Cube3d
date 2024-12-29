/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/29 17:47:06 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void	clear_image(t_game *game)
{
	for (int y = 0; y < S_H; y++)
		for(int x = 0; x < S_W; x++)
			put_pixel(x, y, 0, game->img.img);
}

bool	touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	define_texture(t_game *game, int start, int line_height)
{


	//all if devi aggiungere il controllo sulla direzione del player per capire che faccia del muro stai colpendo
	if (game->map_ref->wall_side == 0)
		game->map_ref->wall_x = game->map_ref->pos_y + game->map_ref->perpwalldist * game->map_ref->ray_dir_y;
	else
		game->map_ref->wall_x = game->map_ref->pos_x + game->map_ref->perpwalldist * game->map_ref->ray_dir_x;
	game->map_ref->wall_x -= floor(game->map_ref->wall_x);
	game->map_ref->tex_x = game->map_ref->wall_x * 128;
	

	if (game->map_ref->wall_side == 0 && game->map_ref->ray_dir_x > 0)
		game->map_ref->tex_x = 128 - game->map_ref->tex_x - 1;
	if (game->map_ref->wall_side == 1 && game->map_ref->ray_dir_y < 0)
		game->map_ref->tex_x = 128 - game->map_ref->tex_x - 1;
	game->map_ref->step = 1.0 * 128 / line_height;
	game->map_ref->tex_pos = (start - S_H / 2
			+ line_height / 2) * game->map_ref->step;
}  
float nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

int get_color(t_game *game, int flag)
{
	game->ray_angle = nor_angle(game->ray_angle);
	if (flag == 0)
	{
		if (game->ray_angle > PI / 2 && game->ray_angle < 3 * (PI / 2))
			return (0x0000FF); // west wall
		else
			return (0xFFFF00); // east wall
	}
	else
	{
		if (game->ray_angle > 0 && game->ray_angle < PI)
			return (0x00FF00); // south wall
		else
			return (0xFF0000); // north wall
	}
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix)
{
	int color;

	color = get_color(game, game->flag);
	while (t_pix < b_pix)
		img_pix_put(game, ray, t_pix++, color);
}

void render_wall(t_game *game, int ray)
{
	double wall_h;
	double b_pix;
	double t_pix;
	double proj_plane_dist = (S_W / 2) / tan(game->player.fov_rd / 2);
	
	game->ray_distance *= cos(nor_angle(game->ray_angle - game->player.angle));
	wall_h = (TILE_SIZE / game->ray_distance) * proj_plane_dist;
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(game, ray, t_pix, b_pix);
}

int wall_hit(float x, float y, t_map *map)
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= map->h_map || x_m >= map->w_map))
		return (0);
	if (map->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
		return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
		return (1);
	}
	return (0);
}

float get_h_inter(t_player *player, t_map *map, float angl)
{
	float h_x;
	float h_y;
	float x_step;
	float y_step;
	int  pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(player->p_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = player->p_x + (h_y - player->p_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, map))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - player->p_x, 2) + pow(h_y - player->p_y, 2)));
}

float get_v_inter(t_player *player, t_map *map, float angl)
{
	float v_x;
	float v_y;
	float x_step;
	float y_step;
	int  pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(player->p_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = player->p_y + (v_x - player->p_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, map))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - player->p_x, 2) + pow(v_y - player->p_y, 2)));
}
int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(game); // check player movement and rotation
	// clear_image(game); // added clear function to reset the screen when moving

	//////////////////////////////////////////////////////////////////
	// Rendering 2d map for Debug:
	//  draw_square(player->p_x, player->p_y, 5, 0x00FF00, game);
	//  draw_map(game);
	//////////////////////////////////////////////////////////////////
	double h_inter;
	double v_inter;
	double angle;

	game->ray_angle = player->angle - (player->fov_rd / 2);
	int i = 0;
	render_background(game);
	while (i < S_W)
	{
		game->flag = 0;
		h_inter = get_h_inter(player, game->map_ref, nor_angle(game->ray_angle));
		v_inter = get_v_inter(player, game->map_ref, nor_angle(game->ray_angle));
		if (v_inter <= h_inter)
			game->ray_distance = v_inter;
		else
		{
			game->ray_distance = h_inter;
			game->flag = 1;
		}
		render_wall(game, i);
		i++;
		game->ray_angle += (player->fov_rd / S_W);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
