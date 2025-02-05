/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:25:35 by giulio            #+#    #+#             */
/*   Updated: 2025/02/05 13:45:35 by giulio           ###   ########.fr       */
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

static int	first_wall(char **map, int i, int end, int start)
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

int last_wall(char **map, int i, int end, int start)
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

int wall_space(t_map *s_map, char **map, int i, int space)
{
	int	space_check;
	int last_char;

	space_check = 0;
	last_char = trim_spaces(map[i]);
	while (1)
	{
		if (!space)
			space = check_space(map[i]);
		else
		{
			space_check = space;
			space += check_space(&map[i][space]);
		}
		if (space_check == space || space == last_char)
			return (0);
		if (!i)
		{
			if (first_other_walls(s_map, map, i, space))
				return (1);
		}
		else
		{
			if (last_other_walls(s_map, map, i, space))
				return (1);
		}
	}
	return (0);
}

int	check_fist_and_last_wall(t_map *s_map, int i, int end, int start)
{
	int	ret;
	int	space;
	char	**map;
	int	space_check;

	map = s_map->map;
	space = 0;
	ret = 0;
	if (i == 0)
	{
		if (first_wall(map, i, end, start))
			ret++;
	}
	else
	{
		if (last_wall(map, i, end, start))
			ret++;
	}
	if (ret)
		return (1);
	int last_char;
	if (wall_space(s_map, map, i, space))
		ret++;
	return (ret);
}
