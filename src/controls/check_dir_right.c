/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:33:38 by adapassa          #+#    #+#             */
/*   Updated: 2025/02/04 13:02:56 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	int	check_direction_right2(t_game *game, int code, int tmp_x, int tmp_y)
{
	float	tmp_wall;

	if (code == 2)
	{
		if (game->map[tmp_y][tmp_x + 1] &&
			game->map[(int)tmp_y][(int)tmp_x + 1] == '1')
		{
			tmp_wall = (float)((tmp_x + 1) * TILE_SIZE);
			if (game->player.p_x >= (tmp_wall - 13))
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

static	int	check_direction_right3(t_game *game, int code, int tmp_x, int tmp_y)
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
	return (0);
}

int	check_direction_right(t_game *game, int code)
{
	int		tmp_x;
	int		tmp_y;
	int		ret;

	tmp_x = (int)(game->player.p_x) / TILE_SIZE;
	tmp_y = (int)(game->player.p_y) / TILE_SIZE;
	ret = 0;
	ret += check_direction_right3(game, code, tmp_x, tmp_y);
	ret += check_direction_right2(game, code, tmp_x, tmp_y);
	return (ret);
}

int	mini_helper2(t_game *game, tmp_x, tmp_y)
{
	float	tmp_wall;

	tmp_wall = 0;
	if (game->map[tmp_y][tmp_x - 1]
		&& game->map[(int)tmp_y][(int)tmp_x - 1] == '1')
	{
		tmp_wall = (float)((tmp_x) * TILE_SIZE);
		if (game->player.p_x <= (tmp_wall + 5))
			return (1);
	}
	return (0);
}
