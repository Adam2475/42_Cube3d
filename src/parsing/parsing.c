/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/09 23:31:14 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	int	check_configuration(t_map *map)  // tochange
{
	if (check_line_config(map, "NO") || check_line_config(map, "SO") 
		|| check_line_config(map, "WE") || check_line_config(map, "EA"))
		return (1);
	// print_map(map->texture);
	if (check_line_config(map, "F") || check_line_config(map, "C"))
		return (1);	
	return (0);
}

int	map_parsing(char **av, t_map *map)
{
	char	*tmp;
	char	**tmp_map; 
	char	*path;

	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!tmp || ft_strcmp(tmp, ".cub") != 0)
		return (1);
	path = ft_strjoin("./", av[1]);
	tmp_map = NULL;
	tmp_map = read_map(path, map); // read full mappa
	if (!tmp_map)
		return (1);
	free(path);
	if (get_map(tmp_map, map) || get_textures(tmp_map, map))	//aggiunge alla struct la matrix mappa e texture
	{
		free_map(map);
		free_matrix(tmp_map);
		return (1);
	}
	free_matrix(tmp_map);
	if (check_characters(map)) // TO MOD;
	{
		free_matrix(map->map);
		return (1);
	}
	if (check_configuration(map))
		return(1);
	printf("----------------------------\n");
	printf("The passed map is valid!\n\n");
	return (0);
}

char	**read_map(char *path, t_map *map) //togliere map
{
	int		fd;
	char	**temp_map;
	char	*temp_line;
	int		i;
	int		count;

	i = 0;
	(void)path; // togliere versione definitiva
	// fd = open(path, O_RDONLY);
	fd = open("/home/giulio/Desktop/42_Cube3d/valid.cub", O_RDONLY);
	if (fd == -1)
		return (NULL);
	count = count_line(fd);
	close(fd);
	// fd = open(path, O_RDONLY); // diocane
	fd = open("/home/giulio/Desktop/42_Cube3d/valid.cub", O_RDONLY); // sul mio pc non funziona il path DIO MERDA
	temp_map = ft_calloc(count + 1, sizeof(char *));
	if (!temp_map)
		return (NULL);
	while ((temp_line = get_next_line(fd)) != NULL) // assigning in control line is forbidden
	{
		temp_map[i] = ft_strdup(temp_line);
		free(temp_line);
		i++; // togliere
	}
	map->total_lines = 0; // togliere
	temp_map[i] = NULL;
	close(fd);
	return (temp_map);
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
		if (!in_texture(tmp[i]))
			check++;
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
	int	j;
	char **mtx;
	int	lines;
	int start;
	int end;
	
	lines = map->map_lines;
	mtx = map->map;
	i = 0;
	while(mtx[i])
	{
		start = skip_spaces(mtx[i]);
		end = trim_spaces(mtx[i]);
		j = start;
		while (mtx[i][j])
		{
			if (i == 0 || i == lines - 1)
			{
				if (mtx[i][j] != '1')
					return (1);
			}
			else if (j == start || j == end - 1)
			{
				if (mtx[i][j] != '1')
				return (1);
			}	
			else if (!ft_strchr("10NSEW ", mtx[i][j]) && mtx[i][j] != '\n')
				return(1);
			if (j == end - 1)
				break;
			j++;
		}
		i++;
	}
	return (0);
}