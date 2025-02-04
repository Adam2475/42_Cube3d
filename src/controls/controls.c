/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:48 by adapassa          #+#    #+#             */
/*   Updated: 2025/02/04 12:52:14 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_up(t_game *game)
{
	int	result;

	result = 0;
	if (!result && game->player.angle >= 3.1 && game->player.angle <= 6.5)
		result = (check_direction_up(game, 0));
	if (!result && game->player.angle >= 1.5
		&& game->player.angle <= 5)
		result = (check_direction_up(game, 1));
	if (!result && ((game->player.angle >= 0
				&& game->player.angle <= 1.5) || game->player.angle > 4.7))
		result = (check_direction_up(game, 2));
	if (!result && game->player.angle >= 0.01
		&& game->player.angle < 3)
		result = (check_direction_up(game, 3));
	return (result);
}

int	check_down(t_game *game)
{
	int	result;

	result = 0;
	if (!result && game->player.angle >= 0.0 && game->player.angle <= 3.1)
		result = (check_direction_down(game, 0));
	if (!result && ((game->player.angle >= 0 && game->player.angle <= 1.5)
			|| game->player.angle >= 4.6))
		result = (check_direction_down(game, 1));
	if (!result && game->player.angle >= 1.5 && game->player.angle <= 4.7)
		result = (check_direction_down(game, 2));
	if (!result && game->player.angle >= 3 && game->player.angle <= 6.4)
		result = (check_direction_down(game, 3));
	return (result);
}

int	check_right(t_game *game)
{
	int	result;

	result = 0;
	if (!result && (game->player.angle > 1.5 && game->player.angle <= 4.8))
		result = (check_direction_right(game, 0));
	if (!result && (game->player.angle >= 0 && game->player.angle <= 4))
		result = (check_direction_right(game, 1));
	if (!result && (((game->player.angle >= 3.3
					&& game->player.angle <= 6) || game->player.angle > 6)))
		result = (check_direction_right(game, 2));
	if (!result && ((game->player.angle >= 0
				&& game->player.angle <= 6) || game->player.angle > 6))
		result = (check_direction_right(game, 3));
	return (result);
}

int	check_collision(t_game *game, int direction)
{
	int	result;

	result = 0;
	if (direction == 1)
		result = check_up(game);
	if (direction == 2)
		result = check_down(game);
	if (direction == 3)
		result = check_left(game);
	if (direction == 4)
		result = check_right(game);
	return (result);
}

void	handle_player_movement(t_game *game,
		float cos_angle, float sin_angle, int speed)
{
	t_player	*player;

	player = &game->player;
	if (player->key_up && !check_collision(game, 1))
	{
		player->p_x += cos_angle * speed;
		player->p_y += sin_angle * speed;
	}
	if (player->key_down && !check_collision(game, 2))
	{
		player->p_x -= cos_angle * speed;
		player->p_y -= sin_angle * speed;
	}
	if (player->key_left && !check_collision(game, 3))
	{
		player->p_x += sin_angle * speed;
		player->p_y -= cos_angle * speed;
	}
	if (player->key_right && !check_collision(game, 4))
	{
		player->p_x -= sin_angle * speed;
		player->p_y += cos_angle * speed;
	}
}
