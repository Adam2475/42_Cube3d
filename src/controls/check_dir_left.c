/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:42:18 by giulio            #+#    #+#             */
/*   Updated: 2025/01/14 15:46:52 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	int	check_direction_left2(t_game *game, int code, int tmp_x, int tmp_y)
{
	float	tmp_wall;

	if (code == 2)
	{
		if (game->map[tmp_y][tmp_x + 1] &&
			game->map[(int)tmp_y][(int)tmp_x + 1] == '1')
		{
			tmp_wall = (float)((tmp_x + 1) * TILE_SIZE);
			if (game->player.p_x >= (tmp_wall - 10))
				return (1);
		}
	}
	else if (code == 3)
	{
		if (game->map[tmp_y + 1][tmp_x] &&
			game->map[(int)tmp_y + 1][(int)tmp_x] == '1')
		{
			tmp_wall = (float)((tmp_y + 1) * TILE_SIZE);
			if (game->player.p_y >= (tmp_wall - 12))
				return (1);
		}
	}
	return (0);
}

static	int	check_direction_left3(t_game *game, int code, int tmp_x, int tmp_y)
{
	float	tmp_wall;

	if (code == 0)
	{
		if (game->map[tmp_y - 1][tmp_x] &&
			game->map[(int)tmp_y - 1][(int)tmp_x] == '1')
		{
			tmp_wall = (float)((tmp_y) * TILE_SIZE);
			if (game->player.p_y <= (tmp_wall + 5))
				return (1);
		}
	}
	else if (code == 1)
	{
		if (game->map[tmp_y][tmp_x - 1] &&
			game->map[(int)tmp_y][(int)tmp_x - 1] == '1')
		{
			tmp_wall = (float)((tmp_x) * TILE_SIZE);
			if (game->player.p_x <= (tmp_wall + 5))
				return (1);
		}
	}
}

int	check_direction_left(t_game *game, int code)
{
	int		tmp_x;
	int		tmp_y;
	float	tmp_wall;
	int		res;

	tmp_x = (int)(game->player.p_x) / TILE_SIZE;
	tmp_y = (int)(game->player.p_y) / TILE_SIZE;
	res = 0;
	res += check_direction_left3(game, code, tmp_x, tmp_y);
	res += check_direction_left2(game, code, tmp_x, tmp_y);
	return (res);
}
