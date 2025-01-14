/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:12:58 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/14 09:25:30 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

float	get_h_inter(t_player *player, t_map *map, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(player->p_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = player->p_x + (h_y - player->p_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0)
		|| (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, map))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - player->p_x, 2) + pow(h_y - player->p_y, 2)));
}

float	get_v_inter(t_player *player, t_map *map, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(player->p_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = player->p_y + (v_x - player->p_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0)
		|| (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, map))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - player->p_x, 2) + pow(v_y - player->p_y, 2)));
}

int	wall_hit(float x, float y, t_map *map)
{
	int	x_m;
	int	y_m;

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

int	calc_tex_x(t_game *game, t_img *texture, int flag)
{
	int				tex_x;
	double			text_perc_px_hit;

	if (!texture)
		return (0);
	if (isinf(game->player.ray_dir_x) || isinf(game->player.ray_dir_y))
		exit(1);
	text_perc_px_hit = calc_wall_px_hit(game, flag) / 64;
	text_perc_px_hit -= floor(text_perc_px_hit);
	tex_x = (int)((text_perc_px_hit) * 64);
	if (texture && texture->width > 0 && tex_x >= texture->width)
		tex_x = texture->width - 1;
	tex_x = int_imax(0, tex_x);
	return (tex_x);
}

int	calc_tex_y(t_img *texture, double tex_pos)
{
	const t_img	*tex;
	int			text_y;

	tex = texture;
	if (!texture)
		return (0);
	text_y = tex_pos * tex->height / 64;
	if (tex && tex->height > 0 && text_y >= tex->height)
		text_y = tex->height - 1;
	text_y = int_imax(0, text_y);
	return (text_y);
}
