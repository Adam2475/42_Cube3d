/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:57:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/09 09:14:31 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	print_map(char **map)
{
	while (*map)
		printf("%s", *map++);
	printf("%c\n", '\n');
}

void	draw_map(t_game *game)
{
	char **map = game->map;
	int color = 0x0000FF;
	int y = 0;
	while (map[y])
	{
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
		y++;
	}
}