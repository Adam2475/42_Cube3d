/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:16:25 by giulio            #+#    #+#             */
/*   Updated: 2025/01/10 18:14:52 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

static void	dup_texture(t_game *game, char *texture, char *dir, int skip)
{
	if (!ft_strcmp(dir, "NO"))
		game->map_data.texture_no = ft_strdup(&texture[2 + skip]);
	else if (!ft_strcmp(dir, "SO"))
		game->map_data.texture_so = ft_strdup(&texture[2 + skip]);
	else if (!ft_strcmp(dir, "WE"))
		game->map_data.texture_we = ft_strdup(&texture[2 + skip]);
	if (!ft_strcmp(dir, "EA"))
		game->map_data.texture_ea = ft_strdup(&texture[2 + skip]);
}

void	assign_texture_path(t_game *game, t_map *map)
{
	int		i;
	int		j;
	int		skip;
	char	**texture;

	skip = 0;
	j = 0;
	i = 0;
	texture = map->texture;
	while (texture[i] && j <= 4)
	{
		skip = skip_spaces(&texture[i][2]);
		if (!ft_strncmp(texture[i], "NO", 2))
			dup_texture(game, texture[i], "NO", skip);
		else if (!ft_strncmp(texture[i], "SO", 2))
			dup_texture(game, texture[i], "SO", skip);
		else if (!ft_strncmp(texture[i], "WE", 2))
			dup_texture(game, texture[i], "WE", skip);
		else if (!ft_strncmp(texture[i], "EA", 2))
			dup_texture(game, texture[i], "EA", skip);
		j++;
		i++;
	}
}

static void	data_address(t_game *game)
{
	void	*tmp_no;
	void	*tmp_so;
	void	*tmp_we;
	void	*tmp_ea;
	int		*tmp_endian;

	tmp_no = game->texture_n.img.mlx_img;
	tmp_so = game->texture_s.img.mlx_img;
	tmp_we = game->texture_w.img.mlx_img;
	tmp_ea = game->texture_e.img.mlx_img;
	tmp_endian = &game->texture_n.img.endian;
	game->texture_n.img.addr = mlx_get_data_addr(tmp_no,
			&game->texture_n.img.bpp,
			&game->texture_n.img.line_len, tmp_endian);
	game->texture_s.img.addr = mlx_get_data_addr(tmp_so,
			&game->texture_s.img.bpp,
			&game->texture_s.img.line_len, tmp_endian);
	game->texture_w.img.addr = mlx_get_data_addr(tmp_we,
			&game->texture_w.img.bpp,
			&game->texture_w.img.line_len, tmp_endian);
	game->texture_e.img.addr = mlx_get_data_addr(tmp_ea,
			&game->texture_e.img.bpp,
			&game->texture_e.img.line_len, tmp_endian);
}

static void	file_to_image(t_game *game)
{
	char	*tmp_no;
	char	*tmp_so;
	char	*tmp_we;
	char	*tmp_ea;

	tmp_no = ft_strdup(game->map_data.texture_no);
	tmp_so = ft_strdup(game->map_data.texture_so);
	tmp_we = ft_strdup(game->map_data.texture_we);
	tmp_ea = ft_strdup(game->map_data.texture_ea);
	game->texture_n.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_no,
			&game->texture_n.img.width, &game->texture_n.img.height);
	game->texture_s.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_so,
			&game->texture_s.img.width, &game->texture_s.img.height);
	game->texture_w.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_we,
			&game->texture_w.img.width, &game->texture_w.img.height);
	game->texture_e.img.mlx_img = mlx_xpm_file_to_image(game->mlx, tmp_ea,
			&game->texture_e.img.width, &game->texture_e.img.height);
	free(tmp_no);
	free(tmp_so);
	free(tmp_we);
	free(tmp_ea);
}

void	create_textures(t_game *game, t_map *map)
{
	assign_texture_path(game, map);
	init_struct(game);
	file_to_image(game);
	data_address(game);
	if (!game->texture_n.img.mlx_img || !game->texture_s.img.mlx_img
		|| !game->texture_w.img.mlx_img || !game->texture_e.img.mlx_img)
		exit(printf("Path to textures does not exist or cannot be accessed"));
}
