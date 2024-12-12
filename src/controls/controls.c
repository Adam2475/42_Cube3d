/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:48 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/12 17:43:23 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	exit_hook(t_game *game)
{
	// (void)player;
	printf("Window Closed\n");
	destroy_image(game);
	free_map(game->map_ref);
	free_textures(game);
	//free_exit(vars);
	exit(1);
	return (0);
}

int		check_collision(t_game *game, int x, int y, int direction, int speed)
{
	int tmp_x = 0;
	int tmp_y = 0;

	/////////////////////////////////////////////
	//Debug
	//printf("Angle: %f\n", game->player.angle);
	//printf("y: %f\n", game->player.p_y);
	//printf("x: %f\n", game->player.p_x);
	//printf("wall pos: %f\n", tmp_wall);
	/////////////////////////////////////////////

	if (direction == 1 && (game->player.angle >= 3.1 && game->player.angle <= 6.5)) // Case for going up in straight line
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y - 1][tmp_x] && game->map[(int)tmp_y - 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y) * BLOCK);
			if (game->player.p_y <= (tmp_wall + 5))
				return (printf("Top collision!!\n"));
		}
	}
	if (direction == 1 && (game->player.angle >= 1 && game->player.angle <= 5)) // Case for going left in straight line
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x - 1] && game->map[(int)tmp_y][(int)tmp_x - 1] == '1')
		{
			float tmp_wall = (float)((tmp_x) * BLOCK);
			if (game->player.p_x <= (tmp_wall + 5))
				return (printf("Top-left collision!!\n"));
		}
	}
	if (direction == 1 && ((game->player.angle >= 0 && game->player.angle <= 1.5) || game->player.angle > 4.7)) // Case for going right in straight line
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x + 1] && game->map[(int)tmp_y][(int)tmp_x + 1] == '1')
		{
			float tmp_wall = (float)((tmp_x + 1) * BLOCK);
			printf("x: %f\n", game->player.p_x);
			printf("wall pos: %f\n", tmp_wall);
			if (game->player.p_x >= (tmp_wall - 13))
				return (printf("Top-right collision!!\n"));
		}
	}
	if (direction == 1 && (game->player.angle >= 0.01 && game->player.angle < 3)) // Case for going down in straight line
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y + 1][tmp_x] && game->map[(int)tmp_y + 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y + 1) * BLOCK);
			printf("y: %f\n", game->player.p_y);
			printf("wall pos: %f\n", tmp_wall);
			if (game->player.p_y >= (tmp_wall - 11))
				return (printf("Top-down collision!!\n"));
		}
	}
/* ------------------------------------------------------------------------------------------------------------------- */ 
	// Down
	if (direction == 2 && (game->player.angle >= 0.0 && game->player.angle <= 3.1)) // Case for pressing down and goind upwards
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y - 1][tmp_x] && game->map[(int)tmp_y - 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y) * BLOCK);
			if (game->player.p_y <= (tmp_wall + 5))
				return (printf("Back-top collision!!\n"));
		}
	}
	if (direction == 2 && ((game->player.angle >= 0 && game->player.angle <= 1.5) || game->player.angle >= 4.6)) // Case for pressing down and going left backwards
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x - 1] && game->map[(int)tmp_y][(int)tmp_x - 1] == '1')
		{
			float tmp_wall = (float)((tmp_x) * BLOCK);
			printf("x: %f\n", game->player.p_x);
			printf("wall pos: %f\n", tmp_wall);
			if (game->player.p_x <= (tmp_wall + 5))
				return (printf("Back-left collision!!\n"));
		}
	}
	// down - right
	if (direction == 2 && (game->player.angle >= 1.5 && game->player.angle <= 4.7)) // Case for pressing down and goind right backwards
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x + 1] && game->map[(int)tmp_y][(int)tmp_x + 1] == '1')
		{
			float tmp_wall = (float)((tmp_x + 1) * BLOCK);
			printf("x: %f\n", game->player.p_x);
			printf("wall pos: %f\n", tmp_wall);
			if (game->player.p_x >= (tmp_wall - 12))
			{
				printf("Back-right collision!!\n");
				return (1);
			}
		}
	}
	// down - down
	if (direction == 2 && (game->player.angle >= 3 && game->player.angle <= 6.4)) // Case for pressing down and going down backwards
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y + 1][tmp_x] && game->map[(int)tmp_y + 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y + 1) * BLOCK);
			if (game->player.p_y >= (tmp_wall - 10))
				return (printf("Back-bottom collision!!\n"));
		}
	}
/* --------------------------------------------------------------------------------------------------------- */ 
	// Left
	if (direction == 3 && (game->player.angle <= 1.5 || game->player.angle >= 4.5)) // Case for going up while pressing the left key
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y - 1][tmp_x] && game->map[(int)tmp_y - 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y) * BLOCK);
			printf("y: %f\n", game->player.p_y);
			printf("wall pos: %f\n", tmp_wall);
			if (game->player.p_y <= (tmp_wall + 5))
				return (printf("Left-top collision!!\n"));
		}
	}
	if (direction == 3 && (game->player.angle >= 3 && game->player.angle <= 6.3)) // Case for going left while pressing left
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x - 1] && game->map[(int)tmp_y][(int)tmp_x - 1] == '1')
		{
			float tmp_wall = (float)((tmp_x) * BLOCK);
			if (game->player.p_x <= (tmp_wall + 5))
				return (printf("Left-left collision\n"));
		}
	}
	if (direction == 3 && ((game->player.angle >= 0 && game->player.angle <= 2) || game->player.angle > 6)) // Case for going right while pressing left
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x + 1] && game->map[(int)tmp_y][(int)tmp_x + 1] == '1')
		{
			float tmp_wall = (float)((tmp_x + 1) * BLOCK);
			printf("y: %f\n", game->player.p_y);
			printf("wall pos: %f\n", tmp_wall);
			if (game->player.p_x >= (tmp_wall - 10))
				return (printf("Left-right collision\n"));
		}
	}
	if (direction == 3 && (game->player.angle >= 1.5 && game->player.angle <= 6)) // Case for pressing left while going down in straight line
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y + 1][tmp_x] && game->map[(int)tmp_y + 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y + 1) * BLOCK);
			if (game->player.p_y >= (tmp_wall - 12))
				return (printf("Left-bottom collision!!\n"));
		}
	}
	/* --------------------------------------------------------------------------------------------------------- */
	// Right
	if (direction == 4 && (game->player.angle > 1.5 && game->player.angle <= 4.8)) // Case for going up while pressing right
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y - 1][tmp_x] && game->map[(int)tmp_y - 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y) * BLOCK);
			if (game->player.p_y <= (tmp_wall + 5))
				return (printf("Collision!!!!\n"));
		}
	}
	if (direction == 4 && (game->player.angle >= 0 && game->player.angle <= 4)) // Case for going left while pressing right
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x - 1] && game->map[(int)tmp_y][(int)tmp_x - 1] == '1')
		{
			float tmp_wall = (float)((tmp_x) * BLOCK);
			if (game->player.p_x <= (tmp_wall + 5))
				return (printf("Collision!!!!\n"));
		}
	}
	if (direction == 4 && ((game->player.angle >= 3.3 && game->player.angle <= 6) || game->player.angle > 6)) // Case for going right while pressing right
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y][tmp_x + 1] && game->map[(int)tmp_y][(int)tmp_x + 1] == '1')
		{
			float tmp_wall = (float)((tmp_x + 1)* BLOCK);
			if (game->player.p_x >= (tmp_wall - 13))
				return (printf("Right-right collision!!\n"));
		}
	}
	if (direction == 4 && ((game->player.angle >= 0 && game->player.angle <= 6) || game->player.angle > 6)) // Case for going down while pressing right
	{
		tmp_x = (int)(game->player.p_x) / BLOCK;
		tmp_y = (int)(game->player.p_y) / BLOCK;
		if (game->map[tmp_y + 1][tmp_x] && game->map[(int)tmp_y + 1][(int)tmp_x] == '1')
		{
			float tmp_wall = (float)((tmp_y + 1) * BLOCK);
			if (game->player.p_y >= (tmp_wall - 12))
				return (printf("Right-bottom collision!!\n"));
		}
	}
	return (0);
}

void	move_player(t_game *game)
{
	t_player *player = &game->player;
	int speed = 3;
	float angle_speed = 0.03;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	int x = player->p_x / BLOCK;
	int y = player->p_y / BLOCK;
	if (player->key_up && !check_collision(game, x, y, 1,  speed))
	{
		player->p_x += cos_angle * speed;
		player->p_y += sin_angle * speed;
	}
	if (player->key_down && !check_collision(game, x, y, 2,  speed))
	{
		player->p_x -= cos_angle * speed;
		player->p_y -= sin_angle * speed;
	}
	if (player->key_left && !check_collision(game, x, y, 3, speed))
	{
		player->p_x += sin_angle * speed;
		player->p_y -= cos_angle * speed;
	}
	if (player->key_right && !check_collision(game, x, y, 4,  speed))
	{
		player->p_x -= sin_angle * speed;
		player->p_y += cos_angle * speed;
	}
}

int	key_press(int keycode, t_player *player)
{
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
