/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:16:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/11 13:28:42 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

// static	void	img_pix_put(t_map *map, int x, int y, int color)
// {
// 	char	*pixel;

// 	if (y < 0 || y > S_H - 1 || x < 0
// 		|| x > S_W - 1)
// 		return ;
// 	pixel = (map->img[4].addr + (y * map->img[4].line_len
// 				+ x * (map->img[4].bpp / 8)));
// 	*(int *)pixel = color;
// }

static	int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	render_background(t_game *game)
{
	t_map *map = game->map_ref;
	// printf("f1: %d\n", *map->f_color[0]);
	// printf("f2: %d\n", *map->f_color[1]);
	// printf("f3: %d\n", *map->f_color[2]);

	// printf("c1: %d\n", *map->c_color[0]);
	// printf("c2: %d\n", *map->c_color[1]);
	// printf("c3: %d\n", *map->c_color[2]);
	int	x;
	int	y;
	int color_f[3];
	int color_c[3];

	color_f[0] = *map->f_color[0];
	color_f[1] = *map->f_color[1];
	color_f[2] = *map->f_color[2];
	color_c[0] = *map->c_color[0];
	color_c[1] = *map->c_color[1];
	color_c[2] = *map->c_color[2];
	x = 0;
	while (x < S_W)
	{
		y = 0;
		while (y < (S_H - 1))
		{
			if (y < (S_H / 2))
				put_pixel(x, y++, 500000, game);
			else
				put_pixel(x, y++, 120000, game);
		}
		// y++;
		// while (y > (S_H / 2))
		// 	put_pixel(x, y++, 60, game);
		x++;
	}
}

static	void	draw_columns(t_player *player, t_game *game, float start_x, float start_y, int i, int end)
{
	while (start_y < end)
		put_pixel(i, start_y++, 255, game); // Renders the walls in 3d
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->p_x;
	float ray_y = player->p_y;

	while (!touch(ray_x, ray_y, game))
	{
		//put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = distance(ray_x - player->p_x, ray_y - player->p_y);
	float height = (BLOCK / dist) * (S_W / 2);
	int start_y = (S_H - height) / 2;
	int end = start_y + height;

	// TODO : Starting texture rendering
	draw_columns(player, game, start_x, start_y, i, end);
}
