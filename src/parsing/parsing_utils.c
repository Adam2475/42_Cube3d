/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:35:29 by giulio            #+#    #+#             */
/*   Updated: 2025/01/07 19:17:14 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	out_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (0);
	return (1);
}

int	in_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
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
	char	*str;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
		{
			free(str);
			break ;
		}
		free(str);
		i++;
	}
	return (i);
}

int	check_texture_acces(char *texture, int i)
{
	int	fd;

	i += skip_spaces(&texture[i]);
	fd = open(&texture[i], O_RDONLY);
	if (fd == -1)
		return (1);
	return (0);
}
