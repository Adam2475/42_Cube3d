/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/26 18:19:12 by girindi          ###   ########.fr       */
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
	if (!get_map(tmp_map, &map))
		free_matrix(tmp_map);
	// get_textures(&map); TO DO
	if (check_characters(&map)) // TO MOD;
	{
		free_matrix(map.clean_map);
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
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	count = count_line(fd);
	close(fd);
	fd = open(path, O_RDONLY);
	temp_map = ft_calloc(count, sizeof(char *));
	while (1)
	{
		temp_line = get_next_line(fd);
		if (temp_line == NULL)
			break ;
		temp_map[i] = ft_strdup(temp_line);
		free(temp_line);
		i++;
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
	map->clean_map = ft_calloc(size + 1, sizeof(char **));
	if (!map->clean_map)
		return (1);
	while (tmp_map[i])
	{
		map->clean_map[j] = ft_strdup(tmp_map[i]);
		j++;
		i++;
	}
	map->clean_map[j] = NULL;
	return (0);
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
int	check_characters(t_map *map)
{
	int	i;
	int	j;
	int	len;
	char **mtx;

	mtx = map->clean_map;
	i = 0;
	len = 0;
	while(mtx[i])
	{
		j = 0;
		len = ft_strlen(mtx[i]);
		while(mtx[i][j])
		{
			if (j == 0 || j == len - 2) // to mod
				if (mtx[i][j] != '1')
					return (1);
			if (!ft_strchr("10NSEW ", mtx[i][j]) && mtx[i][j] != '\n')
				return(1);
			j++;
		}
		i++;
	}
	return (0);
}
