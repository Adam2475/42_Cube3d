/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:16:00 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/16 17:50:30 by giulio           ###   ########.fr       */
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
				put_pixel2(x, y++, color_c, game);
			else
				put_pixel2(x, y++, color_f, game);
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

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float ray_dir_x = cos(start_x);
	float ray_dir_y = sin(start_x);
	float map_x = player->p_x;
	float map_y = player->p_y;	
	double delta_dist_x = fabs(1 / ray_dir_x);
	double delta_dist_y = fabs(1 / ray_dir_y);
	double side_dist_x;
	double side_dist_y;
	
	int step_x;
	int step_y;	
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player->p_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player->p_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player->p_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player->p_y) * delta_dist_y;
	}
	
	int side;
	while (!touch(map_x, map_y, game))
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
	}	
	double wall_dist;
	double wall_x;
	if (side == 0)
		wall_dist = (map_x - player->p_x + (1 - step_x) / 2) / ray_dir_x;
	else
		wall_dist = (map_y - player->p_y + (1 - step_y) / 2) / ray_dir_y;
	int line_height = (int)(S_H / wall_dist * 64); // The line height multiplied for 64 is correct
	int draw_start = -line_height / 2 + S_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + S_H / 2;
	if (draw_end >= S_H)
		draw_end = S_H - 1;
	if (side == 0)
		wall_x = player->p_y + wall_dist * ray_dir_y;
	else
		wall_x = player->p_x + wall_dist * ray_dir_x;	
	wall_x -= floor(wall_x);	
	// Seleziona la texture in base alla direzione
	int *texture;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			texture = game->texture_e.text_value; // Est
		else
			texture = game->texture_w.text_value; // Ovest
	}
	else
	{
		if (ray_dir_y > 0)
			texture = game->texture_s.text_value; // Sud
		else
			texture = game->texture_n.text_value; // Nord
	}	
	// Disegna la colonna della texture direttamente
	for (int y = draw_start; y < draw_end; y++) 
	{
		int tex_y = (int)(((y - draw_start) / (float)line_height) * 64);
		int tex_x = (int)(wall_x * 64);
		if (side == 0 && ray_dir_x > 0) tex_x = 64 - tex_x - 1;
		if (side == 1 && ray_dir_y < 0) tex_x = 64 - tex_x - 1;
		int color = texture[64 * tex_y + tex_x];
		put_pixel(i, y, color, game);
		// printf("wall_dist: %f\n", wall_dist);
		// printf("line_height: %d\n", line_height);
		// printf("tex_x: %d, tex_y: %d\n", tex_x, tex_y);
	}
}


    // Ora determiniamo la direzione del muro e carichiamo la texture corretta
    // if (side == 0)  // Muro verticale
    // {
    //     if (dir_x > 0)  // Est
    //      mlx_put_image_to_window(game->mlx, game->win, game->texture_e.img.img, 0, 0);
    //     else            // Ovest
    //         mlx_put_image_to_window(game->mlx, game->win, game->texture_w.img.img, 0, 0);
    // }
    // else  // Muro orizzontale
    // {
    //     if (dir_y > 0)  // Sud
    //         mlx_put_image_to_window(game->mlx, game->win, game->texture_s.img.img, 0, 0);
    //     else            // Nord
    //         mlx_put_image_to_window(game->mlx, game->win, game->texture_n.img.img, 0, 0);
    // }
	// TODO : Starting texture rendering
// 	draw_columns(player, game, start_x, start_y, i, end);
// }
