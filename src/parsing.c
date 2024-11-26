/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: girindi <girindi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/11/26 16:35:03 by girindi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

// TODO : perform a check on the symbols in the map

int map_parsing(char **av)
{
	char	*tmp;
	char	**tmp_map = NULL; // struct full-MAP
	char	*path;
	t_map	*map = NULL;
	
	// printf("initializing the map!\n");
	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!tmp || ft_strcmp(tmp, ".cub") != 0) // checking the extension of the map
		return (1);
	path = ft_strjoin("./", av[1]);
	map->full_map = read_map(path);
	if (!map->full_map)
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

char **read_map(char *path)
{
	int		fd;
	char	**temp_map;
	char	*temp_line;
	int		i;
	// int		count;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	// count = count_line(fd);
	temp_map = ft_calloc(50, sizeof(char *)); // trova modo meglio dh
	while (1)
	{
		temp_line = get_next_line(fd);
		printf("%s", temp_line);
		if (temp_line == NULL)
			break ;
		// else if (!in_map(temp_line))
		// {
		// 	temp_map[i] = ft_strdup(temp_line);
		// 	free(temp_line);
		// }
		//TO DO				check per effettivo read della mappa e non altri elementi presenti nel file
		i++;
		printf("%d\n", i);
	}
	temp_map[i] = NULL;
	close(fd);
	return (temp_map);
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
	int		r_check;
	int		i;
	char	buffer[50];

	i = 0;
	r_check = 1;
	while (r_check > 0)
	{
		r_check = read(fd, buffer, 50);
		if (r_check == -1)
			return (0);
		else if (r_check == 0)
			break ;
		buffer[r_check] = '\0';
		while (ft_strchr(buffer, '\n') != NULL)
			i++;
	}
	return (i);
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
