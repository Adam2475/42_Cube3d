/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/09 12:48:49 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

// TODO : perform a check on the symbols in the map

// 		if (ft_strncmp(map->texture[i], "SO", 2))
// 			return (1);
// 		if (ft_strncmp(map->texture[i], "WE", 2))
// 			return (1);
// 		if (ft_strncmp(map->texture[i], "EA", 2))
// 			return (1);
// static	int	check_textures(t_map *map, int i)
// {
// 	if (i == 0)
// 	{
// 		if (ft_strncmp(map->texture[i], "NO", 2))
// 			return (1);
// 	}
// 	if (i == 0)
// 	{
// 		if (ft_strncmp(map->texture[i], "NO", 2))
// 			return (1);
// 	}
// 	if (i == 0)
// 	{
// 		if (ft_strncmp(map->texture[i], "NO", 2))
// 			return (1);
// 	}
// 	if (i == 0)
// 	{
// 		if (ft_strncmp(map->texture[i], "NO", 2))
// 			return (1);
// 	}
// }

static	int	check_configuration(t_map *map)
{
	//int	i;

	//i = 0;
	// if (map)
	// {
	// 	printf("Hello form the configuration check!\n\n");
	// 	print_map(map->texture);
	// }
	// while (i <= 3)
	// {
	// 	if (check_textures(map, i))
	// 		return (1);
	// 	i++;
	// }
	return (0);
}

int	check_strt_pos(t_map *map)
{
	int p_found;

	p_found = 0;
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
		j = start;						// TO DO: togliere spazi eventuali dopo il muro
		while (mtx[i][j])
		{
			//printf("%c", mtx[i][j]); // Bada sto stronzo
			if (mtx[i][j] == 'P')
			{
				map->p_init_pos[0] = i;
				map->p_init_pos[1] = j;
				return (0);
			}
			if (j == end - 1)
				break;
			j++;
		}
		i++;
	}
	return (1);
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
	if (!get_map(tmp_map, map) && !get_textures(tmp_map, map))	//aggiunge alla struct la matrix mappa e texture
		free_matrix(tmp_map);
	if (check_characters(map) || check_strt_pos(map)) // TO MOD;
	{
		//printf("Debug: problem with the checks!\n");
		free_matrix(map->map);
		// free_matrix(map.full_map); da aggiungere dopo il get textures
		return (1);
	}
	if (check_configuration(map))
		return(1);
	//printf("----------------------------\n");
	//printf("The passed map is valid!\n\n");
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
	fd = open(path, O_RDONLY);
	//fd = open("/home/giulio/Desktop/42_Cube3d/prova.cub", O_RDONLY);
	if (fd == -1)
		return (NULL);
	count = count_line(fd);
	close(fd);
	fd = open(path, O_RDONLY); // diocane
	//fd = open("/home/giulio/Desktop/42_Cube3d/prova.cub", O_RDONLY); // sul mio pc non funziona il path DIO MERDA
	temp_map = ft_calloc(count, sizeof(char *));
	while ((temp_line = get_next_line(fd)) != NULL) // assigning in control line is forbidden
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
	i = 0;													//https://www.youtube.com/watch?v=G9i78WoBBIU
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
		j = start;						// TO DO: togliere spazi eventuali dopo il muro
		while (mtx[i][j])
		{
			if (i == 0 || i == lines)	// MOD : modificata uscita in caso di carattere 'P' trovato
			{
				if (mtx[i][j] != '1')
					return (1);
			}
			else if (j == start || j == end - 1)
			{
				if (mtx[i][j] != '1')
				return (1);
			}	
			else if (!ft_strchr("10NSEWP", mtx[i][j]) && mtx[i][j] != '\n')
				return(1);
			if (j == end - 1)
				break;
			j++;
		}
		i++;
	}
	map->height_i = i;
	map->width_i = j;
	// printf("%d\n", i);	
	// printf("%d\n", j);
	return (0);
}
