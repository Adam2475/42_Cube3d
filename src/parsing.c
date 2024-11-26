/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/26 21:25:21 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// TODO : perform a check on the symbols in the map

int map_parsing(char **av)
{
	char	*tmp;
	char	**tmp_map = NULL; 
	char	*path;
	t_map	map;

	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!tmp || ft_strcmp(tmp, ".cub") != 0)
		return (1);
	path = ft_strjoin("./", av[1]);
	tmp_map = read_map(path, &map); // read full mappa
	if (!tmp_map)
		return (1);
	if (!get_map(tmp_map, &map) && !get_textures(tmp_map, &map))	//aggiunge alla struct la matrix mappa e texture
		free_matrix(tmp_map);
	if (check_characters(&map)) // TO MOD;
	{
		free_matrix(map.map);
		// free_matrix(map.full_map); da aggiungere dopo il get textures
		return (1);
	}
	printf("The passed map is valid!\n");
	return (0);
}

char	**read_map(char *path, t_map *map)
{
	int		fd;
	char	**temp_map;
	char	*temp_line;
	int		i;
	int		count;

	i = 0;
	(void)path;
	// fd = open(path, O_RDONLY);
	fd = open("/home/giulio/Desktop/42_Cube3d/prova.cub", O_RDONLY);
	if (fd == -1)
		return (NULL);
	count = count_line(fd);
	close(fd);
	// fd = open(path, O_RDONLY);
	fd = open("/home/giulio/Desktop/42_Cube3d/prova.cub", O_RDONLY); // sul mio pc non funziona il path DIO MERDA
	temp_map = ft_calloc(count, sizeof(char *));
	while ((temp_line = get_next_line(fd)) != NULL)
	{
		temp_map[i++] = ft_strdup(temp_line);
		free(temp_line);
	}
	map->total_lines = i;
	temp_map[i] = NULL;
	close(fd);
	return (temp_map);
}

int	get_map(char **tmp_map, t_map *map)
{
	int	i;
	int	j;
	int	size;
	
	j = 0;
	i = 0;
	while (tmp_map[i] && in_map(tmp_map[i]))
			i++;
	size = map->total_lines - i;
	map->texture_lines = i;
	map->map = ft_calloc(size + 1, sizeof(char **));
	if (!map->map)
		return (1);
	while (tmp_map[i])
	{
		map->map[j] = ft_strdup(tmp_map[i]);
		j++;
		i++;
	}
	map->map[j] = NULL;
	return (0);
}

int	get_textures(char **tmp, t_map *map)
{
	int	i;
	int	j;
	int counter;

	counter = 0;
	i = 0;
	j = 0;
	while (i != map->texture_lines)
	{
		if (!trim_textures(tmp[i]))
			counter++;
		i++;
	}
	map->texture = calloc(counter + 1, sizeof(char **));
	if (!map->texture)
		return (1);
	i = 0;
	while (tmp[i] && j != counter)
	{
		if (!trim_textures(tmp[i]))
			map->texture[j++] = ft_strdup(tmp[i]);
		i++;
	}
	map->texture[counter] = NULL;
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
	
	lines = map->total_lines - map->texture_lines - 1;
	mtx = map->map;
	i = 0;
	while(mtx[i])
	{
		start = skip_spaces(mtx[i]);
		end = trim_spaces(mtx[i]);
		j = start;							 // TO DO: togliere spazi eventuali dopo il muro
		while (mtx[i][j])
		{
			if (i == 0 || i == lines)
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
