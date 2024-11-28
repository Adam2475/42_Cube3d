/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:17:09 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/28 14:03:01 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

// Our put_pixel funciton

void	put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= S_W || y >= S_H || x < 0 || y < 0) // check if point is in range
		return ;

	int index = y * game->size_line + x * game->bpp / 8; // put pixel into the buffer
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF; 
	game->data[index + 2] = (color >> 16) & 0xFF;
}

// Our function to draw a square

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}