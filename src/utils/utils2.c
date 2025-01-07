/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:17:09 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/20 14:37:47 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

// Our put_pixel funciton

void	put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= S_W || y >= S_H || x < 0 || y < 0) // check if point is in range
		return ;

	int index = y * game->size_line + x * game->bpp / 8; // put pixel into the buffer
	game->img.addr[index] = color & 0xFF;
	game->img.addr[index + 1] = (color >> 8) & 0xFF; 
	game->img.addr[index + 2] = (color >> 16) & 0xFF;
}

void	put_pixel2(int x, int y, int *color, t_game *game)
{
	if (x >= S_W || y >= S_H || x < 0 || y < 0) // check if point is in range
		return ;

	int index = y * game->size_line + x * game->bpp / 8; // put pixel into the buffer
	game->data[index] = color[0];
	game->data[index + 1] = color[1]; 
	game->data[index + 2] = color[2];
	//game->data[index + 3] = color[3];
	
}

// Our function to draw a square

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game->img.img);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game->img.img);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game->img.img);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game->img.img);
}

int	num_len(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_strnlen(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i <= n)
		i++;
	return (i);
}

char **duplicate_double_pointer(char **original)
{
	size_t i, count = 0;
	char **duplicate;

	// Count the number of strings in the original double pointer
	while (original && original[count])
		count++;

	// Allocate memory for the new double pointer (including NULL terminator)
	duplicate = malloc((count + 1) * sizeof(char *));
	if (!duplicate)
		return NULL;

	// Duplicate each string
	for (i = 0; i < count; i++)
	{
		duplicate[i] = ft_strdup(original[i]);
		if (!duplicate[i])
		{
			// Free previously allocated strings on failure
			while (i > 0)
				free(duplicate[--i]);
			free(duplicate);
			return NULL;
		}
	}
	// free_matrix(original);
	duplicate[count] = NULL;
	return duplicate;
}