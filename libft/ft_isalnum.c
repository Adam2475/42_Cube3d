/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:11:50 by adapassa          #+#    #+#             */
/*   Updated: 2023/12/19 17:32:35 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char c)
{
	if (((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		|| (c <= '9' && c >= '0'))
		return (1);
	return (0);
}
