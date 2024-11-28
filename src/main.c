/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:40:49 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/28 12:29:35 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// Check TO_DO.txt for tasks

int	main(int ac, char **av)
{
	t_map	map; // Struct map is initialized in "map_parsing"
	t_game	game; // Initialized in game_init, hold the window pointer

	if (ac != 2) // If the number of arguments is not 2 quit immediatly
		return (printf("Bad number of arguments!\n"));
	if (map_parsing(av, &map)) // Perform the checks on the map: extension, characters & configuration
		return (printf("Invalid map or configuration!\n"));
	
	//////////////////////////
	// For Debug
	// print_map(map.map);
	// printf("%c\n", '\n');
	// print_map(map.texture);

	if (game_init(av, &map, &game)) // initialize game window
		return (printf("Error while initializing the game\n"));

	draw_square(S_W / 2, S_H / 2, 10, 0x00FF00, &game);
	mlx_loop(game.mlx);
	////////////////////////////////////////////////
	// ??
	// mlx_hook(vars.win, 17, 0, &exit_hook, &vars);
	// mlx_key_hook(vars.win, &key_hook, &vars);
	/////////////////////////////////////////////////
	
	//t_data *data;
	//data = init_argument(); // init the data structure
	//start_the_game(data); // start the game
	return (0);
}
