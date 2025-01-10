/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:12 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/10 15:29:13 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

static	void	assign_texture_path(t_game *game, t_map *map) //to_change: se il path è assoluto deve funzionare ma non c'è un ./ (cambiare strdup)
{
	int	i;
	int	j;
	int skip;

	skip = 0;
	j = 0;
	i = 0;
	while (map->texture[i] && j <= 4)
	{
		skip = skip_spaces(&map->texture[i][2]);
		if (!ft_strncmp(map->texture[i], "NO", 2) || !ft_strncmp(map->texture[i], "SO", 2) 
		|| !ft_strncmp(map->texture[i], "WE", 2) || !ft_strncmp(map->texture[i], "EA", 2))
		{
			if (j == 0)
				game->map_data.texture_no = ft_strdup(&map->texture[0][2 + skip]);
			else if (j == 1)
				game->map_data.texture_so = ft_strdup(&map->texture[1][2 + skip]);
			else if (j == 2)
				game->map_data.texture_we = ft_strdup(&map->texture[2][2 + skip]);
			else if (j == 3)
				game->map_data.texture_ea = ft_strdup(&map->texture[3][2 + skip]);
			j++;
		}
		i++;
	}
}

static	void	init_struct(t_game *game)
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

void	create_textures(t_game *game, t_map *map)
{
	assign_texture_path(game, map);
	char *tmp_no = ft_strdup(game->map_data.texture_no);
	char *tmp_so = ft_strdup(game->map_data.texture_so);
	char *tmp_we = ft_strdup(game->map_data.texture_we);
	char *tmp_ea = ft_strdup(game->map_data.texture_ea);
	init_struct(game);
	game->texture_n.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_no, &game->texture_n.img.width, &game->texture_n.img.height);
	game->texture_s.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_so, &game->texture_s.img.width, &game->texture_s.img.height);
	game->texture_w.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_we, &game->texture_w.img.width, &game->texture_w.img.height);
	game->texture_e.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_ea, &game->texture_e.img.width, &game->texture_e.img.height);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	game->texture_n.img.addr = mlx_get_data_addr(game->texture_n.img.mlx_img, &game->texture_n.img.bpp, &game->texture_n.img.line_len, &game->texture_n.img.endian);
	game->texture_s.img.addr = mlx_get_data_addr(game->texture_s.img.mlx_img, &game->texture_s.img.bpp, &game->texture_s.img.line_len, &game->texture_s.img.endian);
	game->texture_w.img.addr = mlx_get_data_addr(game->texture_w.img.mlx_img, &game->texture_w.img.bpp, &game->texture_w.img.line_len, &game->texture_w.img.endian);
	game->texture_e.img.addr = mlx_get_data_addr(game->texture_e.img.mlx_img, &game->texture_e.img.bpp, &game->texture_e.img.line_len, &game->texture_e.img.endian);
	free(tmp_no);
	free(tmp_so);
	free(tmp_we);
	free(tmp_ea);
	if (!game->texture_n.img.mlx_img || !game->texture_s.img.mlx_img || !game->texture_w.img.mlx_img || !game->texture_e.img.mlx_img)
		exit(printf("Path to textures does not exist or cannot be accessed"));
}

void	init_player(t_player *player, t_map *map)
{
	player->p_x = map->p_init_pos[1] * TILE_SIZE + TILE_SIZE / 2;
	player->p_y = map->p_init_pos[0] * TILE_SIZE + TILE_SIZE / 2;
	player->p_tx = map->p_init_pos[1] * TILE_SIZE;
	player->p_ty = map->p_init_pos[0] * TILE_SIZE;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	init_dir(map, player);
	player->fov_rd = (FOV * PI) / 180;
}

int		game_init(char **av, t_map *map, t_game *game)
{
	(void)av;
	game->mlx = mlx_init();
	game->map = duplicate_double_pointer(map->map);
	game->win = mlx_new_window(game->mlx, S_W, S_H, "Cub3d");
	game->img.img = mlx_new_image(game->mlx, S_W, S_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);
	game->bpp = game->img.bpp; // 2D debug
	game->size_line = game->img.line_len; //2D debug
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	init_dir(t_map *map, t_player *player)
{
	if (map->dir == 'N')
		player->angle = 3 * PI / 2;
	else if (map->dir== 'S')
		player->angle = PI / 2;
	else if (map->dir == 'E')
		player->angle = 0;
	else if (map->dir== 'W')
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
	map->h_map = 6;
	map->w_map = 25;
	map->p_init_pos[0] = -1;
	map->p_init_pos[1] = -1;
}
