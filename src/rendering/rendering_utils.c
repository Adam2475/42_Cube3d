/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/02 18:10:54 by giulio           ###   ########.fr       */
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
// int get_texture_color(t_img *texture, int x, int y)
// {
//     char *pixel;
//     int color;

//     pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
//     color = *(int *)pixel;
//     return color;
// }

// int get_color(t_game *game, int flag, int x, int y)
// {
// 	int	tex_x;
// 	int	tex_y;
// 	double	wall_x;
// 	t_img	*texture;

// 	game->ray_angle = nor_angle(game->ray_angle);
// 	if (flag == 0)
// 	{
// 		if (game->ray_angle > PI / 2 && game->ray_angle < 3 * (PI / 2))
// 			texture = &game->texture_w.img; // west wall
// 		else
// 			texture = &game->texture_e.img;; // east wall
// 		wall_x = game->player.p_y + game->ray_distance * game->player.ray_dir_y;
// 	}
// 	else
// 	{
// 		if (game->ray_angle > 0 && game->ray_angle < PI)
// 			texture = &game->texture_s.img; // south wall
// 		else
// 			texture = &game->texture_n.img; // north wall
// 		 wall_x = game->player.p_x + game->ray_distance * game->player.ray_dir_x;
//     }

//     wall_x -= floor(wall_x);
//     tex_x = (int)(wall_x * (double)texture->width);
//     tex_y = (int)((double)y / S_H * texture->height);

//     return get_texture_color(texture, tex_x, tex_y);
// }


// void draw_wall(t_game *game, int ray, int t_pix, int b_pix)
// {
// 	int color;

// 	color = get_color(game, game->flag, ray, t_pix);
// 	while (t_pix < b_pix)
// 		img_pix_put(game, ray, t_pix++, color);
// }

// void render_wall(t_game *game, int ray)
// {
// 	double wall_h;
// 	double b_pix;
// 	double t_pix;
// 	double proj_plane_dist = (S_W / 2) / tan(game->player.fov_rd / 2);
	
// 	game->ray_distance *= cos(nor_angle(game->ray_angle - game->player.angle));
// 	wall_h = (TILE_SIZE / game->ray_distance) * proj_plane_dist;
// 	b_pix = (S_H / 2) + (wall_h / 2);
// 	t_pix = (S_H / 2) - (wall_h / 2);
// 	if (b_pix > S_H)
// 		b_pix = S_H;
// 	if (t_pix < 0)
// 		t_pix = 0;
// 	draw_wall(game, ray, t_pix, b_pix);
// }
int get_texture_color(t_img *texture, int x, int y)
{
    char *pixel;
    int color;

    pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    color = *(int *)pixel;
    return color;
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix, double wall_h)
{
    int color;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;
    t_img *texture;

    // Select the correct texture based on the wall side
    if (game->flag == 0) // Vertical wall
    {
        if (game->ray_angle > PI / 2 && game->ray_angle < 3 * (PI / 2))
        {
            texture = &game->texture_w.img; // West wall
        }
        else
        {
            texture = &game->texture_e.img; // East wall
        }
    }
    else // Horizontal wall
    {
        if (game->ray_angle > 0 && game->ray_angle < PI)
        {
            texture = &game->texture_s.img; // South wall
        }
        else
        {
            texture = &game->texture_n.img; // North wall
        }
    }

    // Calculate the exact x-coordinate on the wall where the ray hits
    double wall_x;
    if (game->flag == 0)
        wall_x = game->player.p_y + game->ray_distance * game->player.ray_dir_y;
    else
        wall_x = game->player.p_x + game->ray_distance * game->player.ray_dir_x;
    wall_x -= floor(wall_x);

    // Calculate the x-coordinate in the texture
    tex_x = (int)(wall_x * (double)texture->width);
    if ((game->flag == 0 && game->player.ray_dir_x > 0) || (game->flag == 1 && game->player.ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;
	// if (tex_x < 0) 
	// 	tex_x = 0;
	// if (tex_x >= texture->width)
    // 	tex_x = texture->width - 1;
    // Calculate the step to move in the texture for each pixel drawn
    step = 1.0 * texture->height / wall_h;
    tex_pos = (t_pix - S_H / 2 + wall_h / 2) * step;
	printf("Initial tex_pos calculation: %f (t_pix: %d, wall_h: %f, step: %f)\n", tex_pos, t_pix, wall_h, step);

    // Imposta tex_pos a 0 se è negativo
	tex_pos = fmod(tex_pos, 1.0f);
	if (tex_pos < 0) tex_pos += 1.0f;

	if (t_pix < 0)
{
    tex_pos += -t_pix * step;
    t_pix = 0;
}
	// printf("wall_h: %f, tex_pos: %f\n", wall_h, tex_pos);
    // Loop through each pixel from t_pix to b_pix
	// printf("t_pix: %d, b_pix: %d, wall_h: %f, step: %f, tex_pos: %f\n", 
    //    t_pix, b_pix, wall_h, step, tex_pos);
    while (t_pix < b_pix)
    {
        tex_y = (int)tex_pos;
        tex_pos += step;
		if (tex_y < 0) tex_y = 0;
        if (tex_y >= texture->height) tex_y = texture->height - 1;
        color = get_texture_color(texture, tex_x, tex_y);
        img_pix_put(game, ray, t_pix++, color);
    }
	// printf("tex_x: %d, tex_y: %d\n", tex_x, tex_y);
	// printf("tex_x: %d, tex_y: %d, tex_width: %d, tex_height: %d\n", tex_x, tex_y, texture->width, texture->height);
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
	
    draw_wall(game, ray, t_pix, b_pix, wall_h);
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
		game->player.ray_dir_x = cos(game->ray_angle);
		game->player.ray_dir_y = sin(game->ray_angle);
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
