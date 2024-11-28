/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:12 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/28 12:49:24 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// int	game_init(char **av, t_map *map)
// {
// 	(void)av;
// 	printf("Initializing the game window!\n\n");

// 	// Debug
// 	//print_map(map->map);
	
// 	return (0);
// }

int		game_init(char **av, t_map *map, t_game *game)
{
	(void)av;
	(void)map;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, S_W, S_H, "Cub3d");
	game->img = mlx_new_image(game->mlx, S_W, S_H);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}