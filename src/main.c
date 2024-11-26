/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:40:49 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/25 20:35:56 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// TODO : map map parsing
// TODO : add a working gnl to the library
// TODO : initialize the window in game_init

int	main(int ac, char **av)
{
	(void)ac;
	if (ac != 2) // If the number of arguments is not 2 quit immediatly
		return (printf("Bad number of arguments!\n"));
	if (map_parsing(av))
		return (printf("Invalid map passed!\n"));
	if (game_init(av))
		return (printf("Error while initializing the game\n"));
	//t_data *data;
	//data = init_argument(); // init the data structure
	//start_the_game(data); // start the game
	return (0);
}
