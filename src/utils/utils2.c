/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:17:09 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/10 18:22:48 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= S_W || y >= S_H || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->img.addr[index] = color & 0xFF;
	game->img.addr[index + 1] = (color >> 8) & 0xFF;
	game->img.addr[index + 2] = (color >> 16) & 0xFF;
}

void	put_pixel2(int x, int y, int *color, t_game *game)
{
	int	index;

	if (x >= S_W || y >= S_H || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color[0];
	game->data[index + 1] = color[1];
	game->data[index + 2] = color[2];
}

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

char	**duplicate_double_pointer(char **original)
{
	size_t	i;
	size_t	count;
	char	**duplicate;

	i = 0;
	count = 0;
	while (original && original[count])
		count++;
	duplicate = malloc((count + 1) * sizeof(char *));
	if (!duplicate)
		return (NULL);
	for (i = 0; i < count; i++)
	{
		duplicate[i] = ft_strdup(original[i]);
		if (!duplicate[i])
		{
			while (i > 0)
				free(duplicate[--i]);
			free(duplicate);
			return (NULL);
		}
	}
	duplicate[count] = NULL;
	return (duplicate);
}
