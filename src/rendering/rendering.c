/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:16:00 by adapassa          #+#    #+#             */
/*   Updated: 2025/01/07 12:35:48 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	render_background(t_game *game)
{
	t_map *map = game->map_ref;
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
				img_pix_put(game, x, y++, create_trgb(0, color_c[0],
						color_c[1], color_c[2]));
			else
				img_pix_put(game, x, y++, create_trgb(0, color_f[0],
						color_f[1], color_f[2]));
		}
		x++;
	}
}

void	img_pix_put(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > S_H - 1 || x < 0
		|| x > S_W - 1)
		return ;
	pixel = (game->img.addr + (y * game->img.line_len
				+ x * (game->img.bpp / 8)));
	*(int *)pixel = color;
}
