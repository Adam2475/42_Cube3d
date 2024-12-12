/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/11 14:23:19 by adapassa         ###   ########.fr       */
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

// static void define_texture(t_game *game)
// {
// 	if (map->wall_side == 0)
// 		map->wall_x = map->pos_y + map->perpwalldist * map->ray_dir_y;
// 	else
// 		map->wall_x = map->pos_x + map->perpwalldist * map->ray_dir_x;
// 	map->wall_x -= floor(map->wall_x);
// 	map->tex_x = map->wall_x * 128;
// 	if (map->wall_side == 0 && map->ray_dir_x > 0)
// 		map->tex_x = 128 - map->tex_x - 1;
// 	if (map->wall_side == 1 && map->ray_dir_y < 0)
// 		map->tex_x = 128 - map->tex_x - 1;
// 	map->step = 1.0 * 128 / line_height;
// 	map->tex_pos = (start - map->display_height / 2
// 			+ line_height / 2) * map->step;
// }

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
	//define_texture(game);

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
