/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:12 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/13 18:48:31 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	init_player(t_player *player, t_map *map)
{
	player->p_x = map->p_init_pos[1] * TILE_SIZE + TILE_SIZE / 2;
	player->p_y = map->p_init_pos[0] * TILE_SIZE + TILE_SIZE / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	init_dir(map, player);
	player->fov_rd = (FOV * PI) / 180;
}

int	game_init(char **av, t_map *map, t_game *game)
{
	(void)av;
	game->mlx = mlx_init();
	game->map = duplicate_double_pointer(map->map);
	game->win = mlx_new_window(game->mlx, S_W, S_H, "Cub3d");
	game->img.img = mlx_new_image(game->mlx, S_W, S_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->bpp = game->img.bpp;
	game->size_line = game->img.line_len;
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	init_dir(t_map *map, t_player *player)
{
	if (map->dir == 'N')
		player->angle = 3 * PI / 2;
	else if (map->dir == 'S')
		player->angle = PI / 2;
	else if (map->dir == 'E')
		player->angle = 0;
	else if (map->dir == 'W')
		player->angle = PI;
}

void	init_map(t_map *map)
{
	map->texture = NULL;
	map->map = NULL;
	map->c_color = NULL;
	map->f_color = NULL;
	map->c_alloc = 0;
	map->f_alloc = 0;
	map->h_map = 0;
	map->w_map = 0;
	map->p_init_pos[0] = -1;
	map->p_init_pos[1] = -1;
}

void	init_struct(t_game *game)
{
	game->texture_n.img.mlx_img = NULL;
	game->texture_s.img.mlx_img = NULL;
	game->texture_w.img.mlx_img = NULL;
	game->texture_e.img.mlx_img = NULL;
	game->texture_n.img.addr = NULL;
	game->texture_s.img.addr = NULL;
	game->texture_w.img.addr = NULL;
	game->texture_e.img.addr = NULL;
}
