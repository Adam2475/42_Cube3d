/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/13 14:14:21 by adapassa         ###   ########.fr       */
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

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(game); // check player movement and rotation
	//clear_image(game); // added clear function to reset the screen when moving

	//////////////////////////////////////////////////////////////////
	// Rendering 2d map for Debug:
	//  draw_square(player->p_x, player->p_y, 5, 0x00FF00, game);
	//  draw_map(game);
	//////////////////////////////////////////////////////////////////

	// Starting raycasting part
	float fraction = PI / 3 / S_W; // the amount of space from a ray to another
	float start_x = player->angle - PI / 6; // start_x will be the player direction
	int i = 0;
	render_background(game);
	// one iteration for every pixel on the screen width
	while (i < S_W)
	{
		draw_line(player, game, start_x, i);
		// fraction will be the amount of distance from one column to another
		// it's calculated based on : PI / 3 / s_width
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
	
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
