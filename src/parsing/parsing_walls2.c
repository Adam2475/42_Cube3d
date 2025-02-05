/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:25:19 by girindi           #+#    #+#             */
/*   Updated: 2025/02/05 15:28:14 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	check_surrounded_end(char **map, int i, int end, int end_before)
{
	while (end < end_before)
	{
		if (map[i - 1][end_before] != '1')
			return (1);
		end_before--;
	}
	while (end > end_before)
	{
		if (map[i][end] != '1')
			return (1);
		end--;
	}
	return (0);
}

static int	check_surrounded_start(char **map, int i,
	int start, int start_before)
{
	while (start > start_before)
	{
		if (map[i - 1][start_before] != '1')
			return (1);
		start_before++;
	}
	while (start < start_before)
	{
		if (map[i][start] != '1')
			return (1);
		start++;
	}
	return (0);
}

int	check_surrounded_wall(char **map, int i, int start, int end)
{
	int	end_before;
	int	start_before;

	if (map[i][start] != '1' || map[i][end] != '1')
		return (1);
	start_before = skip_spaces(map[i - 1]);
	end_before = trim_spaces(map[i - 1]);
	if (check_surrounded_start(map, i, start, start_before))
		return (1);
	if (check_surrounded_end(map, i, end, end_before))
		return (1);
	return (0);
}
