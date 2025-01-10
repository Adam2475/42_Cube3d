/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/10 18:37:19 by giulio           ###   ########.fr       */
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
			put_pixel(x, y, 0, game);
}

void	define_texture(t_game *game, int start, int line_height)
{
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

int get_texture_color(t_img *texture, int x, int y)
{
    char *pixel;
    int color;

    pixel = texture->addr + ((y * texture->line_len) + (x * texture->bpp / 8));
    color = *(int *)pixel;
    return (color);
}

static int	int_imax(int n1, int n2)
{
	if (n1 >= n2)
		return (n1);
	return (n2);
}

static int calc_tex_y(t_game *game, t_img *texture, double tex_pos)
{
	const t_img	*tex = texture;
	int			text_y;

	if (!texture)
		return (0);
	text_y = tex_pos * tex->height / 64;
	if (tex && tex->height > 0 && text_y >= tex->height)
		text_y = tex->height - 1;
	text_y = int_imax(0, text_y);
	//printf("tex_y: %d\n", text_y);
	return (text_y);
}

static double	calc_wall_px_hit(t_game *game, int flag)
{
	double			wall_px;

	// printf("player ray: %f\n", game->player.ray_dir_x);
	// printf("map ray: %f\n", game->map_ref->ray_dir_x);

	// printf("x: %f\n", game->player.p_x);
	// printf("tx: %f\n", game->player.p_tx);

	if (flag == 0)
		wall_px = game->player.p_y + game->ray_distance * game->player.ray_dir_y;
	else
		wall_px = game->player.p_x + game->ray_distance * game->player.ray_dir_x;
	return (wall_px);
}

static	double	normalize_to_one(double num)
{
	return (num - floor(num));
}

static int calc_tex_x(t_game *game, t_img *texture, int flag)
{
	const t_img		*tex = texture;
	int				text_x;
	int				tex_x;
	double			text_perc_px_hit;
	if (!texture)
		return (0);
	if (isinf(game->player.ray_dir_x) || isinf(game->player.ray_dir_y))
		exit(1);
	//////////////////////////////////////////////////////////////////
	text_perc_px_hit = calc_wall_px_hit(game, flag) / 64;
	text_perc_px_hit -= floor(text_perc_px_hit);
	//////////////////////////////////////////////////////////////////
	tex_x = (int)((text_perc_px_hit) * 64);
	if (texture && texture->width > 0 && tex_x >= texture->width)
		tex_x = texture->width - 1;
	tex_x = int_imax(0, tex_x);;
	return (tex_x);
}

static t_img *define_side(t_game *game)
{
	t_img	*texture;
	if (game->flag == 0)
	{
		if (game->ray_angle > PI / 2 && game->ray_angle < 3 * (PI / 2))
			texture = &game->texture_w.img; // West wall
		else
			texture = &game->texture_e.img; // East wall
	}
	else
	{
		if (game->ray_angle > 0 && game->ray_angle < PI)
			texture = &game->texture_s.img; // South wall
		else
			texture = &game->texture_n.img; // North wall
	}
	return (texture);
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix, double wall_h)
{
	int		color;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	t_img	*texture = define_side(game);

	/////////////////////////////////////////////////////////////////////
	// Calculating texture X point
	tex_x = calc_tex_x(game, texture, game->flag);
	/////////////////////////////////////////////////////////////////////
	// Calc scaled textpos
	step = (1.0 * (double)64 / (double)wall_h); // aka: texture.scale
	tex_pos = (t_pix - (S_H / 2) + wall_h / 2) * step; // aka: scaled_textpos
	/////////////////////////////////////////////////////////////////////;
	while (t_pix < b_pix)
	{
		tex_y = calc_tex_y(game, texture, tex_pos);
		tex_pos += step;
		img_pix_put(game, ray, t_pix++, get_texture_color(texture, tex_x, tex_y));
	}
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
		b_pix = S_H - 1;
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
	if ((y_m >= map->h_map || x_m >= map->w_map || y_m <= 0 || x_m <= 0))
		return (0);
	if (map->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(game);
	clear_image(game);
	 double h_inter;
	 double v_inter;
	 double angle;

	 game->ray_angle = player->angle - (player->fov_rd / 2);
	 game->ray_angle = nor_angle(game->ray_angle);
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
	 	game->ray_angle += (player->fov_rd / S_W);
		game->ray_angle = nor_angle(game->ray_angle);
	 	i++;
	 }
	// draw_map(game);
	// draw_square(player->p_x / TILE_SIZE * BLOCK, player->p_y / TILE_SIZE * BLOCK, 10, 0x00FF00, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
