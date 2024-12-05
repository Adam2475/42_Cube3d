/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:35:29 by giulio            #+#    #+#             */
/*   Updated: 2024/12/05 11:07:26 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	trim_line_textures(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	in_map(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (0);
	return (1);
}

int	count_line(int fd)
{
	int		i;

	i = 0;
	while (1)
	{
		if (get_next_line(fd) == NULL)
			break ;
		i++;
	}
	return (i);
}

int	check_line_config(t_map *map, char *str)
{
	int		i;
	int		j;
	int		check;

	check = 0;
	i = 0;
	while (map->texture[i])
	{
		j = ft_strlen(str);
		if (j == 2 && !ft_strncmp(map->texture[i], str, j))
		{
			if (!check_texture_acces(map->texture[i], j))
				check++;
		}
		else if (j == 1 && !ft_strncmp(map->texture[i], str, j))
		{
			if (!check_colors(map->texture[i], str, j, map))
				check++;
		}
		i++;
	}
	if (check == 1)
		return (0);
	return (1);
}

int check_texture_acces(char *texture, int i)
{
	int	fd;

	i += skip_spaces(&texture[i]);
	fd = open(&texture[i], O_RDONLY);
	if (fd == -1)	
		return (1);
	return (0);
}

int check_colors(char *texture, char *str, int i, t_map *map)
{
	int	j;
	char tmp[3];
	int	num;
	
	i += skip_spaces(texture + i);
	while (texture[i])
	{
		j = 0;
		tmp[0] = '\0';
		num = 0;
		while (texture[i] && (texture[i] >= '0' && texture[i] <= '9'))
		{
			if (j > 3)
				return (1);
			tmp[j++] = texture[i];
			i++;
		}
		tmp[j] = '\0';
		i += skip_spaces(&texture[i]);
		if ((num = check_and_skip_range(texture[i], &texture[i], tmp, map, str[0])) == 0)
			return (1); //free dei colori
		i += num;
	}
	return (0);
}

int	check_and_skip_range(char c, char *str, char *tmp, t_map *map, char type)
{
	int	num;
	int	space;
	int	len;
	int	last;

	space = 0;
	last = 0;
	if (c != ',')
	{
		if (c == '\0')
			last = 1;
		else
			return (0);
	}
	num = ft_atoi(tmp);
	len = num_len(num);
	if (num >= 0 && num <= 255)
	{
		alloc_colors(type, len, num, map);
		space++;
		space += skip_spaces(&str[space]);
		return (space + last);
	}
	else
		return (0);
}

void	alloc_colors(char type, int len, int num, t_map *map)
{
	if (type == 'f')
	{
		if (map->f_alloc == 0)
			map->f_color = malloc(len * sizeof(int));
		map->f_color[map->f_alloc] = num;
		map->f_alloc++;
	}
	else
	{
		if (map->c_alloc == 0)
			map->c_color = malloc(len * sizeof(int));
		map->c_color = malloc(len * sizeof(int));
		map->c_color[map->c_alloc] = num;
		map->c_alloc++;
	}	
}