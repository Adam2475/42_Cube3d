/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:12 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/13 15:57:37 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	add_texture_info(t_game *game)
{
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

static	void	assign_texture_path(t_game *game, t_map *map)
{
	game->map_data.texture_no = ft_strdup(ft_strchr(map->texture[0], '.'));
	game->map_data.texture_so = ft_strdup(ft_strchr(map->texture[1], '.'));
	game->map_data.texture_ea = ft_strdup(ft_strchr(map->texture[3], '.'));
	game->map_data.texture_we = ft_strdup(ft_strchr(map->texture[2], '.'));
}

void	create_textures(t_game *game, t_map *map) // da fuck is wrong with these images?
{
	assign_texture_path(game, map);
	//exit(1);
	char *tmp_no = ft_strdup(game->map_data.texture_ea);
	char *tmp_so = ft_strdup(game->map_data.texture_so);
	char *tmp_we = ft_strdup(game->map_data.texture_we);
	char *tmp_ea = ft_strdup(game->map_data.texture_ea);
	game->texture_n.img.img = mlx_xpm_file_to_image(game->mlx, tmp_no, &game->texture_n.img.width, &game->texture_n.img.height);
	game->texture_s.img.img = mlx_xpm_file_to_image(game->mlx, tmp_so, &game->texture_s.img.width, &game->texture_s.img.height);
	game->texture_w.img.img = mlx_xpm_file_to_image(game->mlx, tmp_we, &game->texture_w.img.width, &game->texture_w.img.height);
	game->texture_e.img.img = mlx_xpm_file_to_image(game->mlx, tmp_ea, &game->texture_e.img.width, &game->texture_e.img.height);
	free(tmp_no);
	free(tmp_so);
	free(tmp_we);
	free(tmp_ea);
	if (!game->texture_n.img.img || !game->texture_s.img.img || !game->texture_w.img.img || !game->texture_e.img.img)
		exit(printf("Path to textures does not exist or cannot be accessed"));
	add_texture_info(game);
}

void	init_player(t_player *player, t_map *map)
{
	player->angle = PI / 2;
	player->p_x = map->p_init_pos[1] * BLOCK;
	player->p_y = map->p_init_pos[0] * BLOCK;
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
	game->map = duplicate_double_pointer(map->map); // duplicate the ptr instead of taking map reference
	game->win = mlx_new_window(game->mlx, S_W, S_H, "Cub3d");
	game->img = mlx_new_image(game->mlx, S_W, S_H);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	init_map(t_map *map)
{
	map->texture = NULL;
	map->map = NULL;
	map->c_color = NULL;
	map->f_color = NULL;
	map->c_alloc = 0;
	map->f_alloc = 0;
}