/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:35:29 by giulio            #+#    #+#             */
/*   Updated: 2024/12/09 23:35:27 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	out_map(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (0);
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

int	in_texture(char *str)
{
	int	i;

	i = skip_spaces(str);
	if (!ft_strncmp(&str[i], "NO", 2) || !ft_strncmp(&str[i], "SO", 2) 
		|| !ft_strncmp(&str[i], "WE", 2) || !ft_strncmp(&str[i], "EA", 2))
		return (0);
	else if (!ft_strncmp(&str[i], "F", 1) || !ft_strncmp(&str[i], "C", 1))
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

int	check_line_config(t_map *map, char *str)  // to_change
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
	char *tmp;
	int	num;
	
	i += skip_spaces(texture + i);
	if (check_len_color(&texture[i]))
		return (1);
	if ((tmp = calloc(4, sizeof(char))) == NULL)
		return (1);
	while (texture[i])
	{
		num = 0;
		tmp[0] = '\0';
		if ((tmp = tmp_num(tmp, &texture[i])) == NULL)
			return (free(tmp), 1);
		i += ft_strlen(tmp);
		i += skip_spaces(&texture[i]);
		num = check_and_skip_range(texture[i], &texture[i],
			tmp, map, str[0]);
		i += num;
		if (num == -1)
			break ;
		else if (num == 0)
				return (free(tmp),1);
	}
	free(tmp);
	return (0);
}

int	check_and_skip_range(char c, char *str, char *tmp, t_map *map, char type)
{
	int	num;
	int	space;

	space = 0;
	if (c != ',')
	{
		if (c != '\0')
			return (0);
	}
	num = ft_atoi(tmp);
	if (num >= 0 && num <= 255)
	{
		alloc_colors(type, num, map);
		if (c != '\0')
		{
			space++;
			space += skip_spaces(&str[space]);
			return (space);
		}
		else
			return (-1);
	}
		return (0);
}

void	alloc_colors(char type, int num, t_map *map)
{
	if (type == 'F')
	{
		if (map->f_alloc == 0)
			map->f_color = malloc(3 * sizeof(int *));
		map->f_color[map->f_alloc] = malloc(1 * sizeof(int));
		map->f_color[map->f_alloc][0] = num;
		map->f_alloc++;
	}
	else
	{
		if (map->c_alloc == 0)
			map->c_color = malloc(3 * sizeof(int *));
		map->c_color[map->c_alloc] = malloc(1 * sizeof(int));
		map->c_color[map->c_alloc][0] = num;
		map->c_alloc++;
	}	
}

int	check_len_color(char *str)
{
	int	check;
	int	i;

	i = 0;
	check = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && (str[i] != ','))
		{
			while (str[i] && str[i] != ' ' && (str[i] != ','))
			{
				if (str[i] < '0' || str[i] > '9')
					return (1);
				i++;
			}
			check++;
		}
		if (str[i])
			i++;
	}
	if (check == 3)
		return (0);
	return (1);
}

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

char	*tmp_num(char *tmp, char *texture)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (texture[i] && (texture[i] >= '0' && texture[i] <= '9'))
	{
		if (j > 3)
			return (NULL);
		tmp[j++] = texture[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}