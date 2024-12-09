/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giulio <giulio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:42:10 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/09 18:51:32 by giulio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	size_t	j;

	if (!s1)
		s1len = 0;
	else
		s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	res = ft_calloc((s1len + s2len + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	free(s1);
	return (res);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

// void	free_int_matrix(char **matrix)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 
// 	if (!matrix)
// 		return ;
	
// 	while (matrix[i])
// 	{
// 		free(matrix[i]);
// 		matrix[i] = NULL;
// 		i++;
// 	}
// 	free(matrix);
// }

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '	')
			return (i);
		i++;
	}
	return (0);
}

int	trim_spaces(char *str)
{
	int	i;

	i = 0;
	i = ft_strlen(str);
	if (str[i - 1] == '\n')
		i--;
	while (i != 0)
	{
		if (str[i] != ' ' && str[i] != '	')
			return (i);
		i--;
	}
	return (0);
}

char *cub3d_strdup(char *str)
{
	int len;
	char *pt1;
	int	i;
	
	i = 0;
	pt1 = NULL;
	while (str[i] == ' ')
		i++;
	len = ft_strlen(str);
	while (str[len - 1] == '\n' || str[len - 1] == ' ') 
		len--;
	pt1 = malloc(sizeof(char) * (len - i + 1));
	if (!pt1)
		return (NULL);
	strncpy(pt1, &str[i], len - i);
	pt1[len - i] = '\0';
	return (pt1);
}
