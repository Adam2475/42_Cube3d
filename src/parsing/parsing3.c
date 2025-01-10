/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:50:44 by giulio            #+#    #+#             */
/*   Updated: 2025/01/10 15:57:22 by giulio           ###   ########.fr       */
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

int	loop_colors(t_map *map, char *tmp, int num, char *texture, char *str)
{
	int	i;

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
		num = check_and_skip_range(texture[i], &texture[i],
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
