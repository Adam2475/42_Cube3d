/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/14 12:32:00 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < S_H)
	{
		while (x < S_W)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_wall(t_game *game, int ray, int t_pix, int b_pix, double wall_h)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	t_img	*texture;

	texture = define_side(game);
	tex_x = calc_tex_x(game, texture, game->flag);
	step = (1.0 * (double)64 / (double)wall_h);
	tex_pos = (t_pix - (S_H / 2) + wall_h / 2) * step;
	while (t_pix < b_pix)
	{
		tex_y = calc_tex_y(texture, tex_pos);
		tex_pos += step;
		img_pix_put(game, ray, t_pix++,
			get_texture_color(texture, tex_x, tex_y));
	}
}

void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;
	double	proj_plane_dist;

	proj_plane_dist = (S_W / 2) / tan(game->player.fov_rd / 2);
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

static void	render_loop(t_game *game, t_player *player)
{
	double	h_inter;
	double	v_inter;
	int		i;

	i = 0;
	while (i < S_W)
	{
		game->player.ray_dir_x = cos(game->ray_angle);
		game->player.ray_dir_y = sin(game->ray_angle);
		game->flag = 0;
		h_inter = get_h_inter(player, game->map_ref,
			nor_angle(game->ray_angle));
		v_inter = get_v_inter(player, game->map_ref,
			nor_angle(game->ray_angle));
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
}

static long long current_time_in_ms(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL) + (time.tv_usec / 1000LL);
}

bool	touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int draw_loop(t_game *game)
{
	t_player *player;
	static long long last_frame_time = 0;
	long long current_time = current_time_in_ms();
	long long elapsed_time = current_time - last_frame_time;

	if (elapsed_time < FRAME_TIME_MS)
		usleep((FRAME_TIME_MS - elapsed_time) * 1000);

	player = &game->player;
	move_player(game);
	clear_image(game);
	render_background(game);
	// draw_square(game->player.p_x, game->player.p_y, 5, 0xFFFF00, game);
	// draw_map(game);
	game->ray_angle = nor_angle(game->ray_angle);
	game->ray_angle = player->angle - (player->fov_rd / 2);

	//////////////////////////////////////////////////////////////
		// Debug:
		// float ray_x = player->p_x;
		// float ray_y = player->p_y;
		// float cos_angle = cos(player->angle);
		// float sin_angle = sin(player->angle);

		// while (!touch(ray_x, ray_y, game))
		// {
		// 	put_pixel(ray_x, ray_y, 0xFF0000, game);
		// 	ray_x += cos_angle;
		// 	ray_y += sin_angle;
		// }
	//////////////////////////////////////////////////////////////
	
	render_loop(game, player);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	last_frame_time = current_time_in_ms();
	return (0);
}
