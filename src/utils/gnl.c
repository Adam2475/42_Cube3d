/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_n_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by girindi           #+#    #+#             */
/*   Updated: 2024/12/05 10:08:36 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char	*read_line(int fd, char *backup, char *buffer)
{
	int		r_check;

	r_check = 1;
	while (r_check > 0)
	{
		r_check = read(fd, buffer, 50);
		if (r_check == -1)
			return (0);
		else if (r_check == 0)
			break ;
		buffer[r_check] = '\0';
		backup = strjoin_free(backup, buffer);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	return (backup);
}

char	*divide_line(char **backup)
{
	char	*ptr_line;
	int		count;
	char	*ptr_tmp;

	count = 0;
	ptr_tmp = *backup;
	while (ptr_tmp && ptr_tmp[count] != '\n' && ptr_tmp[count] != '\0')
		count++;
	ptr_line = ft_substr(ptr_tmp, 0, count + 1);
	*backup = ft_substr(ptr_tmp, count + 1, ft_strlen(ptr_tmp) - count);
	free(ptr_tmp);
	if (*backup && **backup == '\0')
	{
		free(*backup);
		*backup = NULL;
	}
	return (ptr_line);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*ptr_line;
	char		*buffer;

	ptr_line = NULL;
	if (fd < 0)
		return (NULL);
	buffer = ft_calloc((50 + 1), sizeof(char));
	backup = read_line(fd, backup, buffer);
	free(buffer);
	if (!backup)
		return (NULL);
	ptr_line = divide_line(&backup);
	if (!ptr_line || *ptr_line == '\0')
	{
		free(ptr_line);
		return (NULL);
	}
	return (ptr_line);
}