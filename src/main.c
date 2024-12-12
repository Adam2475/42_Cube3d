/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:40:49 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/12 17:31:35 by girindi          ###   ########.fr       */
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
	init_map(&map);
	if (map_parsing(av, &map)) // Perform the checks on the map: extension, characters & configuration
		return (printf("Invalid map or configuration!\n"));
	if (game_init(av, &map, &game)) // initialize game window
		return (printf("Error while initializing the game\n"));
	init_player(&game.player, &map); // initializes the player structure
	 // TODO : initialize textures | OK
	 // TODO : put control on the create textures | ??!
	create_textures(&game, &map);
	game.map_ref = &map;
	mlx_hook(game.win, 17, 0, &exit_hook, &game); // hook for exit button on window
	mlx_hook(game.win, 2, 1L<<0, &key_press, &game.player); // have to revise this fuckin functions
	mlx_hook(game.win, 3, 1L<<1, &key_release, &game.player); // aka : x_event && x-mask
	mlx_loop_hook(game.mlx, draw_loop, &game); // wtf it does??
	mlx_loop(game.mlx); // main loop of the game
	
	//////////////////////////
	// For Debug
	// print_map(map.map);
	// printf("%c\n", '\n');

	//data = init_argument(); // init the data structure
	return (0);
}
