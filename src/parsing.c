/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/25 23:10:25 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// TODO : perform a check on the symbols in the map

int map_parsing(char **av)
{
	char	*tmp;
	char	**tmp_map;

	// printf("initializing the map!\n");
	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!tmp || ft_strcmp(tmp, ".cub") != 0) // checking the extension of the map
		return (1);
	tmp_map = read_map(av[1]);
	if (!tmp_map)
		return (1);
	if (check_characters(tmp_map))
	{
		free_matrix(tmp_map);
		return (1);
	}
	free_matrix(tmp_map);
	printf("The passed map is valid!\n");
	return (0);
}

char **read_map(char *av)
{
	int		fd;
	char	**temp_map;
	char	*temp_line;
	int		i;
	char	*path;

	i = 0;
	path = ft_strjoin("./", av);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	temp_map = ft_calloc(50, sizeof(char *));
	while (1)
	{
		temp_line = get_next_line(fd);
		if (temp_line == NULL)
			break ;
		//TO DO				check per effettivo read della mappa e non altri elementi presenti nel file
		temp_map[i] = ft_strdup(temp_line);
		free(temp_line);
		i++;
	}
	temp_map[i] = NULL;
	close(fd);
	return (temp_map);
}

int	check_characters(char **map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while(map[i])
	{
		j = 0;
		len = ft_strlen(map[i]);
		while(map[i][j])
		{
			if (j == 0 || j == len - 2)
				if (map[i][j] != '1')
					return (1);
			if (!ft_strchr("10NSEW ", map[i][j]) && map[i][j] != '\n')
				return(1);
			j++;
		}
		i++;
	}
	return (0);
}
