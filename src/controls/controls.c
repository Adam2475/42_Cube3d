/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:48 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/03 10:02:59 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	exit_hook(t_player *player)
{
	(void)player;
	printf("Window Closed\n");
	//free_exit(vars);
	exit(1);
	return (0);
}

void	move_player(t_player *player)
{
	int speed = 5;

	if (player->key_up)
		player->p_y -= speed;
	if (player->key_down)
		player->p_y += speed;
	if (player->key_left)
		player->p_x -= speed;
	if (player->key_right)
		player->p_x += speed;
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
	return (0);
}
