/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2025/02/05 17:23:40 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


// int check_valid_texture(char **matrix)
// {
// 	int	i;

// 	i = 0;
// 	while (matrix[i]) 
// 	{
// 	    if (strncmp(matrix[i], "NO", 2) != 0 &&
// 	        strncmp(matrix[i], "SO", 2) != 0 &&
// 	        strncmp(matrix[i], "EA", 2) != 0 &&
// 	        strncmp(matrix[i], "WE", 2) != 0 &&
// 			strncmp(matrix[i], "F", 1) != 0 &&
// 			strncmp(matrix[i], "C", 1) != 0
// 			)
// 	        	return (1); // Errore trovato
// 		i++;
// 	    }
// 	return (0); // Tutti i valori sono validi
// }

int	map_parsing(char **av, t_map *map)
{
	char	**tmp_map;

	tmp_map = check_and_read(av);
	if (!tmp_map)
		return (1);
	if (get_map(tmp_map, map) || get_textures(tmp_map, map))
	{
		free_map(map);
		free_matrix(tmp_map);
		return (1);
	}
	free_matrix(tmp_map);
	if (check_characters(map))
	{
		free_map(map);
		return (1);
	}
	if (check_configuration(map) || check_map_h_w(map))
	{
		free_map(map);
		return (1);
	}
	return (0);
}

char	**check_and_read(char **av)
{
	char	*tmp;
	char	*path;
	char	**tmp_map;

	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!tmp || ft_strcmp(tmp, ".cub") != 0)
		return (NULL);
	path = ft_strjoin("./", av[1]);
	tmp_map = NULL;
	tmp_map = read_map(path);
	free(path);
	if (!tmp_map)
		return (NULL);
	return (tmp_map);
}

int	get_map(char **tmp_map, t_map *map)
{
	int	i;
	int	j;
	int	size;
	int	check_line;

	j = 0;
	i = 0;
	while (tmp_map[i] && in_map(tmp_map[i]))
		i++;
	check_line = i;
	while (tmp_map[check_line] && !in_map(tmp_map[check_line]))
		check_line++;
	size = check_line - i;
	map->map = ft_calloc(size + 1, sizeof(char *));
	if (!map->map)
		return (1);
	while (tmp_map[i] && j != size)
	{
		map->map[j] = ft_strdup(tmp_map[i]);
		j++;
		i++;
	}
	map->map[j] = NULL;
	map->map_lines = size;
	return (0);
}

int	get_textures(char **tmp, t_map *map)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	i = -1;
	j = 0;
	while (tmp[++i])
	{
		if (*tmp[i] == '\n')
			continue ;
		else if (!in_texture(tmp[i]))
			check++;
		else if (check == 6)
			break ;
		else
			return (1);
	}
	if (check != 6)
		return (1);
	i = -1;
	map->texture = calloc(check + 1, sizeof(char *));
	if (!map->texture)
		return (1);
	while (tmp[++i] && check != j)
	{
		if (!in_texture(tmp[i]))
			map->texture[j++] = cub3d_strdup(tmp[i]);
	}
	map->texture[j] = NULL;
	return (0);
}

int	check_characters(t_map *map)
{
	int	i;
	int	start;
	int	end;

	i = -1;
	while (map->map[++i])
	{
		start = skip_spaces(map->map[i]);
		end = trim_spaces(map->map[i]);
		if (i == 0 || i == map->map_lines - 1)
		{
			if (check_fist_and_last_wall(map, i, end, start))
				return (1);
		}
		else if (check_surrounded_wall(map->map, i, start, end))
			return (1);
		if (check_char(map, start, end, i))
			return (1);
	}
	if (map->p_init_pos[0] == -1)
		return (1);
	return (0);
}
