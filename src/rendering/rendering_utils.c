/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/03 12:26:54 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char **save_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111111";
	map[1] = "100000000000000001";
	map[2] = "100000000000000001";
	map[3] = "100000000000000001";
	map[4] = "100000000000000001";
	map[6] = "100000000000000001";
	map[7] = "100000000000000001";
	map[8] = "100000000000000001";
	map[9] = "111111111111111111";
	map[10] = NULL;
	return (map);
}

void	clear_image(t_game *game)
{
	for (int y = 0; y < S_H; y++)
		for(int x = 0; x < S_W; x++)
			put_pixel(x, y, 0, game);
}

bool	touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	char **map = game->map;
	//print_map(map);
	//exit(1);
	printf("%d\n", x);
	printf("%d\n", y);
	print_map(map);
	//printf("%c\n", map[y][x]);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game); // added clear function to reset the screen when moving
	draw_square(player->p_x, player->p_y, 10, 0x00FF00, game);
	draw_map(game);
	// Starting raycasting part
	float ray_x = player->p_x;
	float ray_y = player->p_y;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	// printf("%d\n", ray_x);
	// printf("%d\n", ray_y);

	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_x, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
