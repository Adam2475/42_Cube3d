/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:50:44 by giulio            #+#    #+#             */
/*   Updated: 2025/02/03 12:27:27 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_configuration(t_map *map)
{
	if (check_line_config(map, "NO") || check_line_config(map, "SO")
		|| check_line_config(map, "WE") || check_line_config(map, "EA"))
		return (1);
	if (check_line_config(map, "F") || check_line_config(map, "C"))
		return (1);
	return (0);
}

int	loop_colors(t_map *map, char *tmp, char *texture, char *str)
{
	int	i;
	int	num;

	i = 0;
	while (texture[i])
	{
		num = 0;
		tmp[0] = '\0';
		tmp = tmp_num(tmp, &texture[i]);
		if (tmp == NULL)
			return (free(tmp), 1);
		i += ft_strlen(tmp);
		i += skip_spaces(&texture[i]);
		num = check_and_skip_range(&texture[i],
				tmp, map, str[0]);
		i += num;
		if (num == -1)
			break ;
		else if (num == 0)
			return (free(tmp), 1);
	}
	free(tmp);
	return (0);
}

int	check_other_wall(t_map *map, int i, int j)
{
	if (i == 0)
	{
		while (map->map[i])
		{
			if (map->map[i][j] == '1')
				return (0);
			if (i == map->map_lines)
				return (1);
			i++;
		}
	}
	else
	{
		while (map->map[i])
		{
			if (map->map[i][j] == '1')
				return (0);
			if (i == 0)
				return (1);
			i--;
		}
	}
	return (0);
}

static int	check_mid_full_walls(t_map *map, int i)
{
	int	skip;
	int	end;
	int	len_before;
	int	len;

	skip = skip_spaces(map->map[i - 1]);
	end = trim_spaces(map->map[i - 1]);
	len_before = ft_strlen(map->map[i - 1]);
	len_before -= skip + end;
	len = ft_strlen(map->map[i]);
	while (len - len_before != 0)
	{
		if (map->map[i][len_before] != '1')
		{
			if (map->map[i - 1][len_before] != '1'
			&& (map->map[i + 1][len_before]
			&& map->map[i + 1][len_before] != '1'))
				return (1);
		}
		len_before ++;
	}
	return (0);
}

int	check_map_h_w(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
			j++;
		if (j > map->w_map)
		{
			map->w_map = j;
			if (i != 0 && i != map->map_lines)
			{
				if (check_mid_full_walls(map, i))
					return (1);
			}
		}
		i++;
	}
	map->h_map = i;
	return (0);
}
