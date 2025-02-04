/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:48:32 by adapassa          #+#    #+#             */
/*   Updated: 2025/02/04 12:52:39 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	move_player(t_game *game)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 5;
	angle_speed = 0.05;
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	if (game->player.left_rotate)
		game->player.angle -= angle_speed;
	if (game->player.right_rotate)
		game->player.angle += angle_speed;
	if (game->player.angle > 2 * PI)
		game->player.angle = 0;
	if (game->player.angle < 0)
		game->player.angle = 2 * PI;
	handle_player_movement(game, cos_angle, sin_angle, speed);
}

int	exit_hook(t_game *game)
{
	printf("Window Closed\n");
	destroy_image(game);
	free_matrix(game->map);
	free_map(game->map_ref);
	free_textures(game);
	exit(1);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
		exit_hook(game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

int	check_left(t_game *game)
{
	int	result;

	result = 0;
	if (!result && (game->player.angle <= 1.5 || game->player.angle >= 4.5))
		result = (check_direction_left(game, 0));
	if (!result && (game->player.angle >= 3 && game->player.angle <= 6.3))
		result = (check_direction_left(game, 1));
	if (!result && (((game->player.angle >= 0
					&& game->player.angle <= 3.3) || game->player.angle > 6)))
		result = (check_direction_left(game, 2));
	if (!result && (game->player.angle >= 1.5 && game->player.angle <= 6))
		result = (check_direction_left(game, 3));
	return (result);
}
