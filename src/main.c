/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:40:49 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/05 13:48:50 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// Check TO_DO.txt for tasks

int	main(int ac, char **av)
{
	t_map		map; // Struct map is initialized in "map_parsing"
	t_game		game; // Initialized in game_init, hold the window pointer

	if (ac != 2) // If the number of arguments is not 2 quit immediatly
		return (printf("Bad number of arguments!\n"));
	if (map_parsing(av, &map)) // Perform the checks on the map: extension, characters & configuration
		return (printf("Invalid map or configuration!\n"));
	if (game_init(av, &map, &game)) // initialize game window
		return (printf("Error while initializing the game\n"));
	init_player(&game.player, &map); // initializes the player structure

	// printf("%f\n", game.player.p_x);
	// printf("%f\n", game.player.p_y);

	mlx_hook(game.win, 17, 0, &exit_hook, &game.player); // hook for exit button on window
	mlx_hook(game.win, 2, 1L<<0, &key_press, &game.player); // have to revise this fuckin functions
	mlx_hook(game.win, 3, 1L<<1, &key_release, &game.player); // aka : x_event && x-mask
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
