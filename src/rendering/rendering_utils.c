/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/14 18:33:09 by giulio           ###   ########.fr       */
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
	t_player *player = &game->player;
	move_player(game);
	clear_image(game); // added clear function to reset the screen when moving

	//printf("----------------------------\n");
	//print_map(game->map);
	// printf("%f\n", player->p_x);
	// printf("%f\n", player->p_y);
	//////////////////////////////////////////////////////////////////
	// Rendering 2d map for Debug:
	// draw_square(player->p_x, player->p_y, 5, 0x00FF00, game);
	// draw_map(game);

	// Starting raycasting part

	float fraction = PI / 3 / S_W;
	float start_x = player->angle - PI / 6;
	int i = 0;

	render_background(game);

	while (i < S_W)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	/////////////////////////////////////////////
	//Debug:
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
	////////////////////////////////////////////////
	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
