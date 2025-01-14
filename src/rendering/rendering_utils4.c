/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:08:26 by giulio            #+#    #+#             */
/*   Updated: 2025/01/14 15:33:15 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + ((y * texture->line_len) + (x * texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

double	calc_wall_px_hit(t_game *game, int flag)
{
	double	wall_px;

	if (flag == 0)
		wall_px = game->player.p_y + game->ray_distance
			* game->player.ray_dir_y;
	else
		wall_px = game->player.p_x + game->ray_distance
			* game->player.ray_dir_x;
	return (wall_px);
}

t_img	*define_side(t_game *game)
{
	t_img	*texture;

	if (game->flag == 0)
	{
		if (game->ray_angle > PI / 2 && game->ray_angle < 3 * (PI / 2))
			texture = &game->texture_w.img;
		else
			texture = &game->texture_e.img;
	}
	else
	{
		if (game->ray_angle > 0 && game->ray_angle < PI)
			texture = &game->texture_s.img;
		else
			texture = &game->texture_n.img;
	}
	return (texture);
}

int	int_imax(int n1, int n2)
{
	if (n1 >= n2)
		return (n1);
	return (n2);
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < S_H)
	{
		while (x < S_W)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		x = 0;
		y++;
	}
}
