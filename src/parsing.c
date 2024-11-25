/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/25 13:24:16 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// TODO : perform a check on the symbols in the map

int map_parsing(char **av)
{
	char	*tmp;
	//char	*tmp_map;

	printf("initializing the map!\n");
	tmp = ft_strnstr(av[1], ".ber", ft_strlen(av[1]));
	if (!tmp || ft_strcmp(tmp, ".ber") != 0) // checking the extension of the map
		return (1);
	// write into tmp map the map and then check the symbols
	// parse_map();
	printf("The passed map is valid!\n");
	return (0);
}