/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:25:35 by giulio            #+#    #+#             */
/*   Updated: 2025/02/03 12:36:22 by giulio           ###   ########.fr       */
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

int	check_fist_and_last_wall(t_map *map, int i, int end)
{
	int	end_check;

	if (i == 0)
		end_check = trim_spaces(map->map[i + 1]);
	else
		end_check = trim_spaces(map->map[i - 1]);
	if (ft_strnlen(map->map[i], end) != ft_strnlen(map->map[i + 1], end_check))
		return (1);
}
