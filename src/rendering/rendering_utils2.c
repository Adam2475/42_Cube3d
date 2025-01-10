/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:12:58 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/07 11:41:44 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

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

bool	touch(float px, float py, t_game *game)
{
	int x = px / TILE_SIZE;
	int y = py / TILE_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}
