/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:16:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/05 13:33:17 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->p_x;
	float ray_y = player->p_y;

	while (!touch(ray_x, ray_y, game))
	{
		//put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = distance(ray_x - player->p_x, ray_y - player->p_y);
	player->collision_var = dist;
	float height = (BLOCK / dist) * (S_W / 2);
	int start_y = (S_H - height) / 2;
	int end = start_y + height;

	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}
