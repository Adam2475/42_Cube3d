/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:31 by giulio            #+#    #+#             */
/*   Updated: 2024/12/09 23:38:05 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	free_colors(t_map *map)
{
	int	i;

	i = 0;
	if (map->f_alloc)
	{
		while (i != map->f_alloc)
		{
			free(map->f_color[i]);
			map->f_color[i] = NULL;
			i++;
		}
		free(map->f_color);
	}
	i = 0;
	if (map->c_alloc)
	{
		while (i != map->c_alloc)
		{
			free(map->c_color[i]);
			map->c_color[i] = NULL;
			i++;
		}
		free(map->c_color);
	}
	
}


void	free_map(t_map *map)
{
	free_matrix(map->map);
	free_matrix(map->texture);
	free_colors(map);
}