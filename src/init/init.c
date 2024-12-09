/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:12 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/09 13:08:48 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

static void assign_textures(t_game *game, t_map *map)
{
	char *tmp = NULL;
	tmp = ft_strchr(map->texture[0], '.');
	game->map_data.texture_no = ft_strdup(tmp);
	tmp = ft_strchr(map->texture[1], '.');
	game->map_data.texture_so = ft_strdup(tmp);
	tmp = ft_strchr(map->texture[2], '.');
	game->map_data.texture_we = ft_strdup(tmp);
	tmp = ft_strchr(map->texture[3], '.');
	game->map_data.texture_ea = ft_strdup(tmp);
}

void	add_texture_info(t_game *game)
{
	printf("hello world");
	game->texture_n.text_value = (int *)mlx_get_data_addr(game->texture_n.img.img,
			&game->texture_n.img.bpp, &game->texture_n.img.line_len,
			&game->texture_n.img.endian);
	game->texture_s.text_value = (int *)mlx_get_data_addr(game->texture_s.img.img,
			&game->texture_s.img.bpp, &game->texture_s.img.line_len,
			&game->texture_s.img.endian);
	game->texture_e.text_value = (int *)mlx_get_data_addr(game->texture_e.img.img,
			&game->texture_e.img.bpp, &game->texture_e.img.line_len,
			&game->texture_e.img.endian);
	game->texture_w.text_value = (int *)mlx_get_data_addr(game->texture_w.img.img,
			&game->texture_w.img.bpp, &game->texture_w.img.line_len,
			&game->texture_w.img.endian);
}

static void assign_size(t_game *game)
{
	// game->texture_n.img.width
	// game->texture_n.img.height

	// game->texture_s.img.width
	// game->texture_s.img.height

	// game->texture_w.img.width
	// game->texture_w.img.height

	// game->texture_e.img.width
	// game->texture_e.img.height
	return ;
}

void	create_textures(t_game *game, t_map *map) // da fuck is wrong with these images?
{
	assign_textures(game, map);
	assign_size(game);
	char path[ft_strlen(game->map_data.texture_no)];
	char path2[ft_strlen(game->map_data.texture_so)];
	// char path3[ft_strlen(game->map_data.texture_ea)];
	// char path4[ft_strlen(game->map_data.texture_we)];
	ft_memcpy(path, game->map_data.texture_no, ft_strlen(game->map_data.texture_no) - 1);
	ft_memcpy(path2, game->map_data.texture_so, ft_strlen(game->map_data.texture_so) - 1);
	// ft_memcpy(path4, game->map_data.texture_we, ft_strlen(game->map_data.texture_we) - 1);
	// ft_memcpy(path3, game->map_data.texture_ea, ft_strlen(game->map_data.texture_ea) - 1);
	game->texture_n.img.img = mlx_xpm_file_to_image(game->mlx, path, &game->texture_n.img.width, &game->texture_n.img.height);
	game->texture_s.img.img = mlx_xpm_file_to_image(game->mlx, path2, &game->texture_s.img.width, &game->texture_s.img.height);
	game->texture_w.img.img = mlx_xpm_file_to_image(game->mlx, "./assets/mossy.xpm", &game->texture_w.img.width, &game->texture_w.img.height);
	game->texture_e.img.img = mlx_xpm_file_to_image(game->mlx, "./assets/redbrick.xpm", &game->texture_e.img.width, &game->texture_e.img.height);
	if (!game->texture_n.img.img || !game->texture_s.img.img || !game->texture_w.img.img || !game->texture_e.img.img)
		exit(printf("Path to textures does not exist or cannot be accessed"));
	add_texture_info(game);
}

void	init_player(t_player *player, t_map *map)
{
	player->angle = PI / 2;
	player->p_x = map->p_init_pos[1] * BLOCK; //S_W;
	player->p_y = map->p_init_pos[0] * BLOCK; //S_H / map->height_i;
	// printf("\nx: %d\n", map->p_init_pos[1]);
	// printf("\ny: %d\n", map->p_init_pos[0]);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int		game_init(char **av, t_map *map, t_game *game)
{
	(void)av;
	game->mlx = mlx_init();
	game->map = map->map;
	game->win = mlx_new_window(game->mlx, S_W, S_H, "Cub3d");
	game->img = mlx_new_image(game->mlx, S_W, S_H);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}