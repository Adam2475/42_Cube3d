/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:50:44 by giulio            #+#    #+#             */
/*   Updated: 2025/01/13 18:51:54 by girindi          ###   ########.fr       */
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

char	**check_alloc_path(char *path)
{
	int		fd;
	int		count;
	char	**temp_map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	count = count_line(fd);
	close(fd);
	temp_map = ft_calloc(count + 1, sizeof(char *));
	if (!temp_map)
		return (NULL);
	return (temp_map);
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


int	check_other_wall(t_map *map, int i, int j, int end)
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

void	init_map_h_w(t_map *map)
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
			map->w_map = j;
		i++;
	}
	map->h_map = i;
}
