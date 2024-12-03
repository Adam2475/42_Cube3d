/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:12 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/03 09:50:04 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	init_player(t_player *player)
{
	player->p_x = S_W / 2;
	player->p_y = S_H / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
}

int		game_init(char **av, t_map *map, t_game *game)
{
	//init_player(&game->player);
	(void)av;
	(void)map;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, S_W, S_H, "Cub3d");
	game->img = mlx_new_image(game->mlx, S_W, S_H);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}