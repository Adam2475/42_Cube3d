/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:30:59 by girindi           #+#    #+#             */
/*   Updated: 2025/02/05 15:46:46 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	line_is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_space(char *str)
{
	int	i;

	i = skip_spaces(str);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '0')
			return (i);
		i++;
	}
	return (0);
}

int	space_checker(char *map_line, int space, int *space_check)
{
	if (!space)
		space = check_space(map_line);
	else
	{
		*space_check = space;
		space += check_space(&map_line[space]);
	}
	return (space);
}

static int	check_other_first(t_map *map, int i, int j)
{
	while (map->map[i])
	{
		if (map->map[i][j] == '1')
		{
			if (map->map[i][j + 1] != '1')
				return (1);
			else
				return (0);
		}
		if (i == map->map_lines)
			return (1);
		i++;
	}
	return (0);
}

int	check_other_wall(t_map *map, int i, int j)
{
	if (i == 0)
	{
		if (check_other_first(map, i, j))
			return (1);
		return (0);
	}
	else
	{
		while (map->map[i])
		{
			if (map->map[i][j] == '1')
			{
				if (map->map[i][j - 1] != '1')
					return (1);
				else
					return (0);
			}
			if (i == 0)
				return (1);
			i--;
		}
	}
	return (0);
}
