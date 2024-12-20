/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:31 by giulio            #+#    #+#             */
/*   Updated: 2024/12/20 14:40:37 by girindi          ###   ########.fr       */
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

void	free_textures(t_game *game)
{
	if (game->map_data.texture_no)
		free(game->map_data.texture_no);
	if (game->map_data.texture_so)
		free(game->map_data.texture_so);
	if (game->map_data.texture_we)
		free(game->map_data.texture_we);
	if (game->map_data.texture_ea)
		free(game->map_data.texture_ea);
}

void	destroy_image(t_game *game)
{
	mlx_destroy_image(game->mlx, game->texture_n.img.img);
	mlx_destroy_image(game->mlx, game->texture_s.img.img);
	mlx_destroy_image(game->mlx, game->texture_e.img.img);
	mlx_destroy_image(game->mlx, game->texture_w.img.img);
	// mlx_destroy_image(game->mlx, game->img); //todo
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}