/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:16:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/03 10:23:13 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	clear_image(t_game *game)
{
	for (int y = 0; y < S_H; y++)
		for(int x = 0; x < S_W; x++)
			put_pixel(x, y, 0, game);
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game); // added clear function to reset the screen when moving
	draw_square(player->p_x, player->p_y, 5, 0x00FF00, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}