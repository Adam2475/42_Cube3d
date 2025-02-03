/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:48 by adapassa          #+#    #+#             */
/*   Updated: 2025/02/03 12:38:54 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

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

int	check_collision(t_game *game, int direction)
{
	int	result;

	result = 0;
	if (direction == 1)
	{
		if (!result && game->player.angle >= 3.1 && game->player.angle <= 6.5)
			result = (check_direction_up(game, 0));
		if (!result && game->player.angle >= 1.5
			&& game->player.angle <= 5) // Case for going left in straight line
			result = (check_direction_up(game, 1));
		if (!result && ((game->player.angle >= 0
			&& game->player.angle <= 1.5) || game->player.angle > 4.7)) // Case for going right in straight line
			result = (check_direction_up(game, 2));
		if (!result && game->player.angle >= 0.01
			&& game->player.angle < 3) // Case for going down in straight line
			result = (check_direction_up(game, 3));
	}
/* ------------------------------------------------------------------------------------------------------------------- */ 
	if (direction == 2)
	{
		if (!result && game->player.angle >= 0.0 && game->player.angle <= 3.1) // Case for pressing down and goind upwards
			result = (check_direction_down(game, 0));
		if (!result && ((game->player.angle >= 0 && game->player.angle <= 1.5)
			|| game->player.angle >= 4.6)) // Case for pressing down and going left backwards
			result = (check_direction_down(game, 1));
		if (!result && game->player.angle >= 1.5 && game->player.angle <= 4.7) // Case for pressing down and goind right backwards
			result = (check_direction_down(game, 2));
		if (!result && game->player.angle >= 3 && game->player.angle <= 6.4) // Case for pressing down and going down backwards
			result = (check_direction_down(game, 3));
	}
/* --------------------------------------------------------------------------------------------------------- */
	if (direction == 3)
	{
		if (!result && game->player.angle <= 1.5 || game->player.angle >= 4.5) // Case for going up while pressing the left key
			result = (check_direction_left(game, 0));
		if (!result && game->player.angle >= 3 && game->player.angle <= 6.3) // Case for going left while pressing left
			result = (check_direction_left(game, 1));
		if (!result && ((game->player.angle >= 0 && game->player.angle <= 3.3) || game->player.angle > 6)) // Case for going right while pressing left
			result = (check_direction_left(game, 2));
		if (!result && game->player.angle >= 1.5 && game->player.angle <= 6) // Case for pressing left while going down in straight line
			result = (check_direction_left(game, 3));
	}
/* --------------------------------------------------------------------------------------------------------- */
	if (direction == 4)
	{
		if (!result && game->player.angle > 1.5 && game->player.angle <= 4.8) // Case for going up while pressing right
			result = (check_direction_right(game, 0));
		if (!result && game->player.angle >= 0 && game->player.angle <= 4) // Case for going left while pressing right
			result = (check_direction_right(game, 1));
		if (!result && ((game->player.angle >= 3.3 && game->player.angle <= 6) || game->player.angle > 6)) // Case for going right while pressing right
			result = (check_direction_right(game, 2));
		if (!result && (game->player.angle >= 0 && game->player.angle <= 6) || game->player.angle > 6) // Case for going down while pressing right
			result = (check_direction_right(game, 3));
	}
	return (result);
}

static	void	handle_player_movement(t_game *game,
		float cos_angle, float sin_angle, int speed)
{
	t_player *player = &game->player;
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

int	key_press(int keycode, t_game *game)
{
	t_player *player;

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
