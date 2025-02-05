/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:04:20 by giulio            #+#    #+#             */
/*   Updated: 2025/02/05 13:48:52 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	first_check_wall(char **map, int i, int end, int start)
{
	int	start_after;
	int	end_after;
	
	start_after = skip_spaces(map[i + 1]);
	end_after = trim_spaces(map[i + 1]);
	while (start_after < start)
	{
		if (map[i + 1][start_after] != '1')
			return (1);
		start_after++;
	}
	while (end_after > end)
	{
		if (map[i + 1][end_after] != '1')
			return (1);
		end_after--;
	}
	return (0);
}

int	last_check_wall(char **map, int i, int end, int start)
{
	int	start_before;
	int	end_before;

	start_before = skip_spaces(map[i - 1]);
	end_before = trim_spaces(map[i - 1]);
	while (start_before < start)
	{
		if (map[i - 1][start_before] != '1')
			return (1);
		start_before++;
	}
	while (end_before > end)
	{
		if (map[i - 1][end_before] != '1')
			return (1);
		end_before--;
	}
	return (0);
}

int	first_other_walls(t_map *s_map, char **map, int i, int space)
{
	while (i != s_map->map_lines - 1)
	{
		if (map[i + 1][space] != '1')
		{
			if ((map[i + 1][space + 1] != '1') && (map[i + 1][space - 1] != 1))
				return (1);
		}
		else
			return (0);
		i++;
	}
	return (0);
}

int	last_other_walls(t_map *s_map, char **map, int i, int space)
{
	while (i != 0)
	{
		if (map[i - 1][space] != '1')
		{
			if ((map[i - 1][space + 1] != '1') && (map[i - 1][space - 1] != 1))
				return (1);
		}
		else
			return (0);
		i--;
	}
	return (0);
}